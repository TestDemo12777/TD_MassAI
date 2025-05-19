// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmartObjectTypes.h"
#include "Spatial/PointHashGrid3.h"
#include "Subsystems/WorldSubsystem.h"
#include "TD_MassAI/MassAI/Traits/AgentTrait.h"
#include "BuildingSubsystem.generated.h"

typedef UE::Geometry::TPointHashGrid3<FMassEntityHandle, Chaos::FReal> ItemHashGrid3D;

USTRUCT(BlueprintType)
struct TD_MASSAI_API FBuild
{
	GENERATED_BODY()
	
	FBuild() {}
	FBuild(const FSmartObjectHandle& BuildingRequest, int FloorsNeeded)
	{
		this->BuildingRequest = BuildingRequest;
		this->FloorSeeded = FloorsNeeded;
	}
	bool operator ==(const FBuild& otherBuilding)const
	{
		return otherBuilding.BuildingRequest == this->BuildingRequest;
	}

	UPROPERTY( )
	FSmartObjectHandle BuildingRequest;
	
	UPROPERTY( )
	int32 FloorSeeded = 1;
};


/**
 * 
 */
UCLASS()
class TD_MASSAI_API UBuildingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void AddResourceQueue(FSmartObjectHandle& Handle);

	UFUNCTION()
	void AddAgent(const FMassEntityHandle& Entity);

	UFUNCTION(Blueprintcallable)
	void AddBuilding(const FSmartObjectHandle& BuildingRequest, int Floors = 1);
	
	UFUNCTION()
	bool ClaimFloor(FSmartObjectHandle& OutBuilding);

	bool FindItem(const FVector& Location, float Radius, ETD_ResourceType ResourceType, FMassEntityHandle& OutItemHandle) const;
	int GetQueuedBuildings()const { return QueuedBuildings.Num();}
	void GetQueuedResources(TArray<FSmartObjectHandle>& OutQueuedResources) const { OutQueuedResources = QueuedResources; }
	bool ClaimResource(FSmartObjectHandle& OutResourceHandle);

	UPROPERTY()
	FMassEntityHandle Agent;
	TArray<FBuild> QueuedBuildings;
	TArray<FMassEntityHandle> Agents;
	TArray<FSmartObjectHandle> QueuedResources;

	ItemHashGrid3D ItemHashGrid = ItemHashGrid3D(500.f, FMassEntityHandle());
};
