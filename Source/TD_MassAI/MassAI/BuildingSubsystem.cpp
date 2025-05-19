// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSubsystem.h"

#include "Traits/ItemTrait.h"

void UBuildingSubsystem::AddResourceQueue(FSmartObjectHandle& Handle)
{
	if (QueuedResources.Find(Handle) == INDEX_NONE)
	{
		QueuedResources.Emplace(Handle);
	}
}

void UBuildingSubsystem::AddAgent(const FMassEntityHandle& Entity)
{
	Agents.Emplace(Entity);
}

void UBuildingSubsystem::AddBuilding(const FSmartObjectHandle& BuildingRequest, int Floors)
{
	QueuedBuildings.Emplace(FBuild(BuildingRequest, Floors));
}

bool UBuildingSubsystem::ClaimFloor(FSmartObjectHandle& OutBuilding)
{
	bool bSucceed = false;
	if (QueuedBuildings.Num() > 0)
	{
		FBuild& Build = QueuedBuildings[0];
		OutBuilding = Build.BuildingRequest;
		Build.FloorSeeded--;
		if (Build.FloorSeeded <= 0)
		{
			QueuedBuildings.RemoveAt(0);
		}
		bSucceed = true;
	}
	return bSucceed;
}

bool UBuildingSubsystem::FindItem(const FVector& Location, float Radius, ETD_ResourceType ResourceType,
	FMassEntityHandle& OutItemHandle) const
{
	FMassEntityManager& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(*GetWorld());
	const TPair<FMassEntityHandle, float> ItemHandle = ItemHashGrid.FindNearestInRadius(Location, Radius, [this, &Location, &EntityManager](const FMassEntityHandle& Handle)
	{
		if (!EntityManager.IsEntityValid(Handle))
			return FLT_MAX;
		FVector& OtherLocation = EntityManager.GetFragmentDataPtr<FItemFragment>(Handle)->OldLocation;
		return (float)FVector::Distance(OtherLocation, Location);
	}, [this, &ResourceType, &EntityManager](const FMassEntityHandle& Handle)
	{
		if (!EntityManager.IsEntityValid(Handle))
			return true;
		FItemFragment& Item = EntityManager.GetFragmentDataChecked<FItemFragment>(Handle);
		return Item.bClaimed || Item.ItemType != ResourceType;
	});

	OutItemHandle = ItemHandle.Key;
	return EntityManager.IsEntityValid(ItemHandle.Key);
}

bool UBuildingSubsystem::ClaimResource(FSmartObjectHandle& OutResourceHandle)
{
	bool bSucceed = false;
	if (QueuedResources.Num() > 0)
	{
		OutResourceHandle = QueuedResources[0];
		QueuedResources.RemoveAt(0);
		bSucceed = true;
	}
	return bSucceed;
}
