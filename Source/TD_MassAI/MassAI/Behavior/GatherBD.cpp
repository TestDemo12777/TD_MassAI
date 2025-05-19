// Fill out your copyright notice in the Description page of Project Settings.


#include "GatherBD.h"

#include "MassCommonFragments.h"
#include "MassEntityConfigAsset.h"
#include "MassSpawnerSubsystem.h"
#include "SmartObjectComponent.h"
#include "SmartObjectSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "MassSmartObjectFragments.h"
#include "TD_MassAI/MassAI/Traits/ItemTrait.h"

void UGatherBD::Activate(FMassCommandBuffer& CommandBuffer, const FMassBehaviorEntityContext& EntityContext) const
{
	Super::Activate(CommandBuffer, EntityContext);

	FAgentFragment& Agent = EntityContext.EntityView.GetFragmentData<FAgentFragment>();

	Agent.ResourceHandle.Invalidate();
}

void UGatherBD::Deactivate(FMassCommandBuffer& CommandBuffer, const FMassBehaviorEntityContext& EntityContext) const
{
	Super::Deactivate(CommandBuffer, EntityContext);

	UWorld* TempWorld = EntityContext.SmartObjectSubsystem.GetWorld();

	if (TempWorld)
	{
		UMassSpawnerSubsystem* SpawnerSubsystem = TempWorld->GetSubsystem<UMassSpawnerSubsystem>();
		APawn* TempPawn = UGameplayStatics::GetPlayerPawn(EntityContext.SmartObjectSubsystem.GetWorld(), 0);

		TArray<FMassEntityHandle> Item;
		const FMassEntityTemplate& EntityTemplate = ItemConfig->GetConfig().GetOrCreateEntityTemplate(*TempWorld);
		SpawnerSubsystem->SpawnEntities(EntityTemplate, 4, Item);

		for (const FMassEntityHandle& EntityHandle : Item)
		{
			const FVector& SpawnLoc = EntityContext.EntityView.GetFragmentDataPtr<FTransformFragment>()->GetTransform().GetLocation();

			FItemFragment ItemFragment;
			ItemFragment.ItemType = ResourceType;
			ItemFragment.OldLocation = SpawnLoc;
			
			CommandBuffer.PushCommand<FMassCommandAddFragmentInstances>(EntityHandle, ItemFragment);
		}

		const FMassSmartObjectUserFragment& SmartObjectUserFragment = EntityContext.EntityView.GetFragmentData<FMassSmartObjectUserFragment>();
		if (USmartObjectComponent* SmartObjectComponent = EntityContext.SmartObjectSubsystem.GetSmartObjectComponent(SmartObjectUserFragment.InteractionHandle))
		{
			CommandBuffer.PushCommand<FMassDeferredCommand<EMassCommandOperationType::Destroy>>([SmartObjectComponent, EntityContext](FMassEntityManager& )
			{
				EntityContext.SmartObjectSubsystem.UnregisterSmartObject(*SmartObjectComponent);
				SmartObjectComponent->GetOwner()->Destroy();
			});
		}
	}
}
