// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructLevel.h"

#include "MassCommandBuffer.h"
#include "TD_MassAI/MassAI/Construction.h"

void UConstructLevel::Activate(FMassCommandBuffer& CommandBuffer, const FMassBehaviorEntityContext& EntityContext) const
{
	Super::Activate(CommandBuffer, EntityContext);

	// CommandBuffer.PushCommand(FMassCommandAddTag(EntityContext.EntityView.GetEntity(), FConstFloorTag::StaticStruct()));
	// CommandBuffer.PushCommand<FMassCommandAddTag<FConstFloorTag>>();
	CommandBuffer.AddTag<FConstFloorTag>(EntityContext.EntityView.GetEntity());
}

void UConstructLevel::Deactivate(FMassCommandBuffer& CommandBuffer,
	const FMassBehaviorEntityContext& EntityContext) const
{
	Super::Deactivate(CommandBuffer, EntityContext);
}
