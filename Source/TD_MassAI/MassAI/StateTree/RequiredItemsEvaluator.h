// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassCommonFragments.h"
#include "MassStateTreeTypes.h"
#include "SmartObjectSubsystem.h"
#include "MassEntitySubsystem.h"
#include "TD_MassAI/MassAI/BuildingSubsystem.h"
#include "TD_MassAI/MassAI/Traits/AgentTrait.h"
#include "RequiredItemsEvaluator.generated.h"

USTRUCT(BlueprintType)
struct TD_MASSAI_API FRequiredItemsEvaluatorData
{
	GENERATED_BODY()

	/** 筛选智能对象请求结果 */
	UPROPERTY(EditAnywhere, Category = Output)
	FSmartObjectRequestFilter Filter;

	/** 智能对象得句柄 */
	UPROPERTY(EditAnywhere, Category = Output)
	FSmartObjectHandle SmartObjectHandle;

	/** Mass 实体得句柄 */
	UPROPERTY(EditAnywhere, Category = Output)
	FMassEntityHandle ItemHandle;

	/** 是否找到了智能对象 */
	UPROPERTY(EditAnywhere, Category = Output)
	bool bFoundSmartObject =false;

	/** 是否找到了物品 */
	UPROPERTY(EditAnywhere, Category = Output)
	bool bFoundItemHandle = false;
};

USTRUCT(BlueprintType)
struct TD_MASSAI_API FRequiredItemsEvaluator : public FMassStateTreeEvaluatorBase
{
	GENERATED_BODY()
	virtual bool Link(FStateTreeLinker& Linker) override;
	virtual const UStruct* GetInstanceDataType() const override { return FRequiredItemsEvaluatorData::StaticStruct(); }
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

	TStateTreeExternalDataHandle<FAgentFragment> AgentHandle;
	TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;
	TStateTreeExternalDataHandle<UMassEntitySubsystem> EntitySubsystemHandle;
	TStateTreeExternalDataHandle<FTransformFragment> TransformHandle;
	TStateTreeExternalDataHandle<UBuildingSubsystem> BuildingSubsystemHandle;

	TStateTreeExternalDataHandle<bool> FoundSmartObjectHandle;
	TStateTreeExternalDataHandle<FSmartObjectRequestFilter> FilterHandle;
	TStateTreeExternalDataHandle<bool> FoundItemHandle;
	TStateTreeExternalDataHandle<FSmartObjectHandle> SmartObjectHandle;
	TStateTreeExternalDataHandle<FMassEntityHandle> ItemHandle;
};
