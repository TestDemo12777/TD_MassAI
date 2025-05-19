// Fill out your copyright notice in the Description page of Project Settings.


#include "Construction.h"

#include "MassExecutionContext.h"
#include "MassSmartObjectFragments.h"
#include "SmartObjectComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Traits/AgentTrait.h"

UConstruction::UConstruction()
{
	ObservedType = FConstFloorTag::StaticStruct();
	Operation = EMassObservedOperation::Add;
}

void UConstruction::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ParallelForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& ExecutionContext)
	{
		TConstArrayView<FMassSmartObjectUserFragment> SmartObjFragments = ExecutionContext.GetFragmentView<FMassSmartObjectUserFragment>();
		TArrayView<FAgentFragment> AgentFragments = ExecutionContext.GetMutableFragmentView<FAgentFragment>();

		for (int32 EntityIndex = 0; EntityIndex < ExecutionContext.GetNumEntities(); ++EntityIndex)
		{
			const FMassSmartObjectUserFragment& SmartObjFragment = SmartObjFragments[EntityIndex];
			FAgentFragment& Agent = AgentFragments[EntityIndex];

			if (const USmartObjectComponent* SmartObjectComponent = SmartObjectSubsystem->GetSmartObjectComponent(SmartObjFragment.InteractionHandle))
			{
				const AActor* Actor = SmartObjectComponent->GetOwner();

				UInstancedStaticMeshComponent* InstancedStaticMeshComponent = Actor->FindComponentByClass<UInstancedStaticMeshComponent>();
				FTransform Transform;
				Transform.SetLocation(FVector(0., 0., IncrementHeight * InstancedStaticMeshComponent->GetInstanceCount()));
				InstancedStaticMeshComponent->AddInstance(Transform);

				Agent.BuildingHandle = FSmartObjectHandle::Invalid;
				ExecutionContext.Defer().RemoveTag<FConstFloorTag>(ExecutionContext.GetEntity(EntityIndex));

				int32* ResourceAmount = Agent.Inventory.Find(ETD_ResourceType::Rock);
				if (ResourceAmount)
				{
					*ResourceAmount -= 1;
				}
				ResourceAmount = Agent.Inventory.Find(ETD_ResourceType::Tree);
				if (ResourceAmount)
				{
					*ResourceAmount -= 1;
				}
			}
			
		}
	});
}

void UConstruction::ConfigureQueries()
{
	EntityQuery.AddRequirement<FAgentFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassSmartObjectUserFragment>(EMassFragmentAccess::ReadOnly);
}

void UConstruction::Initialize(UObject& Owner)
{
	Super::Initialize(Owner);

	SmartObjectSubsystem = UWorld::GetSubsystem<USmartObjectSubsystem>(Owner.GetWorld());
}
