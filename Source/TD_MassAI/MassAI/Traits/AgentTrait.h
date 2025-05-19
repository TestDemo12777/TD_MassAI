// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "MassEntityTypes.h"
#include "MassObserverProcessor.h"
#include "SmartObjectTypes.h"
#include "AgentTrait.generated.h"

UENUM(BlueprintType)
enum class ETD_ResourceType : uint8
{
	Tree,
	Rock
};

USTRUCT(BlueprintType)
struct TD_MASSAI_API FAgentFragment : public FMassFragment
{
	GENERATED_BODY()

	/** 资源类型对应得库存数量 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "")
	TMap<ETD_ResourceType, int32> Inventory;
	
	UPROPERTY()
	FSmartObjectHandle BuildingHandle;
	
	UPROPERTY()
	FSmartObjectHandle ResourceHandle;
	
	UPROPERTY()
	TArray<FMassEntityHandle> QueuedItems;
};

USTRUCT(BlueprintType)
struct TD_MASSAI_API FAgentParameters : public FMassSharedFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere);
	TMap<ETD_ResourceType, int32> DefaultRequiredResources;
};

USTRUCT(BlueprintType)
struct TD_MASSAI_API FAgent : public FMassTag
{
	GENERATED_BODY()
	
};

class UBuildingSubsystem;
class USmartObjectSubsystem;

/**
 * 
 */
UCLASS()
class TD_MASSAI_API UAgentTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

public:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;

protected:
	UPROPERTY(EditAnywhere)
	FAgentParameters AgentParameters;
};

UCLASS()
class UAgentInitializer : public UMassObserverProcessor
{
	GENERATED_BODY()

public:
	UAgentInitializer();
	
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	virtual void ConfigureQueries() override;
	virtual void Initialize(UObject& Owner) override;

	TObjectPtr<UBuildingSubsystem> MovementSubsystem;
	TObjectPtr<USmartObjectSubsystem> SmartObjectSubsystem;

	FMassEntityQuery EntityQuery;
};


