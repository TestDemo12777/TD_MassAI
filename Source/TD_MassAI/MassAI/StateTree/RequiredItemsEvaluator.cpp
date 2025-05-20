// Fill out your copyright notice in the Description page of Project Settings.


#include "RequiredItemsEvaluator.h"

#include "StateTreeLinker.h"

bool FRequiredItemsEvaluator::Link(FStateTreeLinker& Linker)
{
	Linker.LinkExternalData(AgentHandle);
	Linker.LinkExternalData(SmartObjectSubsystemHandle);
	Linker.LinkExternalData(EntitySubsystemHandle);
	Linker.LinkExternalData(TransformHandle);
	Linker.LinkExternalData(BuildingSubsystemHandle);

	// Linker.LinkExternalData()

	return true;
}

void FRequiredItemsEvaluator::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	
}
