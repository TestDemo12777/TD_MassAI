// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassObserverProcessor.h"
#include "Construction.generated.h"

USTRUCT(BlueprintType)
struct TD_MASSAI_API FConstFloorTag : public FMassTag
{
	GENERATED_BODY()
	
};

class USmartObjectSubsystem;

/**
 * 
 */
UCLASS()
class TD_MASSAI_API UConstruction : public UMassObserverProcessor
{
	GENERATED_BODY()
public:
	UConstruction();
	
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	virtual void ConfigureQueries() override;
	virtual void Initialize(UObject& Owner) override;

	UPROPERTY()
	TObjectPtr<USmartObjectSubsystem> SmartObjectSubsystem;

	float IncrementHeight = 100.f;
	
	FMassEntityQuery EntityQuery;
};
