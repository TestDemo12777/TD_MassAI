// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTrait.h"

#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "MassRepresentationFragments.h"
#include "TD_MassAI/MassAI/BuildingSubsystem.h"

void UItemTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment<FItemFragment>();
}

UItemProcessor::UItemProcessor()
{
}

void UItemProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ParallelForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& ExecutionContext)
	{
		TConstArrayView<FTransformFragment> Transforms = ExecutionContext.GetFragmentView<FTransformFragment>();
		TArrayView<FItemFragment> ItemFragments = ExecutionContext.GetMutableFragmentView<FItemFragment>();

		for (int32 EntityIndex = 0; EntityIndex < ExecutionContext.GetNumEntities(); ++EntityIndex)
		{
			const FVector& Loc = Transforms[EntityIndex].GetTransform().GetLocation();
			FItemFragment& Item = ItemFragments[EntityIndex];

			BuildingSubsystem->ItemHashGrid.UpdatePoint(ExecutionContext.GetEntity(EntityIndex), Item.OldLocation, Loc);
			Item.OldLocation = Loc;
		}
	});
}

void UItemProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FItemFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddTagRequirement<FItemAddedToGrid>(EMassFragmentPresence::All);
}

void UItemProcessor::Initialize(UObject& Owner)
{
	Super::Initialize(Owner);

	BuildingSubsystem = Owner.GetWorld()->GetSubsystem<UBuildingSubsystem>();
}

UItemInitializerProcessor::UItemInitializerProcessor()
{
	bAutoRegisterWithObserverRegistry = true;
	ObservedType = FTransformFragment::StaticStruct();
	Operation = EMassObservedOperation::Add;
}

void UItemInitializerProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// Super::Execute(EntityManager, Context);

	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		TArrayView<FTransformFragment> Transforms = Context.GetMutableFragmentView<FTransformFragment>();
		TArrayView<FItemFragment> ItemFragments = Context.GetMutableFragmentView<FItemFragment>();

		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			FTransform& T = Transforms[EntityIndex].GetMutableTransform();
			FItemFragment& I = ItemFragments[EntityIndex];

			if (T.GetLocation() == FVector::ZeroVector)
			{
				I.OldLocation.X += FMath::FRandRange(-100.f, 100.f);
				I.OldLocation.Y += FMath::FRandRange(-100.f, 100.f);

				T.SetLocation(I.OldLocation);
			}

			BuildingSubsystem->ItemHashGrid.InsertPoint(Context.GetEntity(EntityIndex), I.OldLocation);
			
			Context.Defer().AddTag<FItemAddedToGrid>(Context.GetEntity(EntityIndex));
		}
	});
}

void UItemInitializerProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FItemFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassRepresentationFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassRepresentationLODFragment>(EMassFragmentAccess::ReadOnly);
}

void UItemInitializerProcessor::Initialize(UObject& Owner)
{
	Super::Initialize(Owner);

	BuildingSubsystem = Owner.GetWorld()->GetSubsystem<UBuildingSubsystem>();
}
