// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AgentTrait.h"
#include "MassEntityTraitBase.h"
#include "MassEntityTypes.h"
#include "ItemTrait.generated.h"

class UMassRepresentationSubsystem;
class UBuildingSubsystem;

USTRUCT(BlueprintType)
struct TD_MASSAI_API FItemFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY()
	ETD_ResourceType ItemType;

	UPROPERTY()
	FVector OldLocation;

	UPROPERTY()
	bool bClaimed = false;
};

USTRUCT(BlueprintType)
struct TD_MASSAI_API FItemAddedToGrid : public FMassTag
{
	GENERATED_BODY()

};

/**
 * 
 */
UCLASS()
class TD_MASSAI_API UItemTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

public:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};

UCLASS()
class UItemProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:
	UItemProcessor();
	
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	virtual void ConfigureQueries() override;
	virtual void Initialize(UObject& Owner) override;

	FMassEntityQuery EntityQuery;

	UPROPERTY()
	UBuildingSubsystem* BuildingSubsystem;

	UPROPERTY()
	UMassRepresentationSubsystem* RepresentationSubsystem;
};

UCLASS()
class UItemInitializerProcessor : public UMassObserverProcessor
{
	GENERATED_BODY()

public:
	UItemInitializerProcessor();
	
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	virtual void ConfigureQueries() override;
	virtual void Initialize(UObject& Owner) override;

	FMassEntityQuery EntityQuery;

	UPROPERTY()
	UBuildingSubsystem* BuildingSubsystem;

	UPROPERTY()
	UMassRepresentationSubsystem* RepresentationSubsystem;
};
