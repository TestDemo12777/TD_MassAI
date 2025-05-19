// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceActor.h"

#include "BuildingSubsystem.h"
#include "SmartObjectComponent.h"

// Sets default values
AResourceActor::AResourceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);
}

// Called when the game starts or when spawned
void AResourceActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResourceActor::AddResourceQueue()
{
	if (const USmartObjectComponent* SmartObjectComponent = FindComponentByClass<USmartObjectComponent>())
	{
		FSmartObjectHandle Handle = SmartObjectComponent->GetRegisteredHandle();
		GetWorld()->GetSubsystem<UBuildingSubsystem>()->AddResourceQueue(Handle);
	}
}

