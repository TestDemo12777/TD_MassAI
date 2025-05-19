// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassSmartObjectBehaviorDefinition.h"
#include "TD_MassAI/MassAI/Traits/AgentTrait.h"
#include "GatherBD.generated.h"

class UMassEntityConfigAsset;
/**
 * 
 */
UCLASS()
class TD_MASSAI_API UGatherBD : public USmartObjectMassBehaviorDefinition
{
	GENERATED_BODY()

public:
	virtual void Activate(FMassCommandBuffer& CommandBuffer, const FMassBehaviorEntityContext& EntityContext) const override;
	virtual void Deactivate(FMassCommandBuffer& CommandBuffer, const FMassBehaviorEntityContext& EntityContext) const override;

	UPROPERTY(EditDefaultsOnly)
	int32 ResourceAmount = 1;

	UPROPERTY(EditDefaultsOnly)
	ETD_ResourceType ResourceType;

	UPROPERTY(EditDefaultsOnly)
	UMassEntityConfigAsset* ItemConfig;
};
