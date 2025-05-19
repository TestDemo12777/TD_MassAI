// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingActor.h"

#include "BuildingSubsystem.h"
#include "SmartObjectComponent.h"

// Sets default values
ABuildingActor::ABuildingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SmartObjectComponent = CreateDefaultSubobject<USmartObjectComponent>("SmartObjectComponent");
}

// Called when the game starts or when spawned
void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();

	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;
	TimerDelegate.BindLambda([this]()
	{
		GetWorld()->GetSubsystem<UBuildingSubsystem>()->AddBuilding(SmartObjectComponent->GetRegisteredHandle(), Floors);
	});
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);
}

// Called every frame
void ABuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

