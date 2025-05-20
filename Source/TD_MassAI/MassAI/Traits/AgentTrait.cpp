// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentTrait.h"

#include "MassEntitySubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "MassRepresentationFragments.h"
#include "TD_MassAI/MassAI/BuildingSubsystem.h"

void UAgentTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	UMassEntitySubsystem* EntitySubsystem = UWorld::GetSubsystem<UMassEntitySubsystem>(&World);
	FMassEntityManager& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
	BuildContext.AddFragment<FAgentFragment>();
	BuildContext.AddTag<FAgent>();

	const FSharedStruct StateTreeFragment = EntityManager.GetOrCreateSharedFragment(AgentParameters);
	BuildContext.AddSharedFragment(StateTreeFragment);
}

UAgentInitializer::UAgentInitializer()
	: EntityQuery(*this)
{
	ObservedType = FAgentFragment::StaticStruct();
	Operation = EMassObservedOperation::Add;
}

void UAgentInitializer::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// Super::Execute(EntityManager, Context);

	EntityQuery.ParallelForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		UBuildingSubsystem* BuildingSubsystem = GetWorld()->GetSubsystem<UBuildingSubsystem>();

		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			BuildingSubsystem->AddAgent(Context.GetEntity(EntityIndex));
		}
	});
}

void UAgentInitializer::ConfigureQueries()
{
	// Super::ConfigureQueries();

	EntityQuery.AddRequirement<FAgentFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddSharedRequirement<FAgentParameters>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddTagRequirement<FAgent>(EMassFragmentPresence::All);
	EntityQuery.AddRequirement<FMassRepresentationFragment>(EMassFragmentAccess::ReadWrite);
}

void UAgentInitializer::Initialize(UObject& Owner)
{
	Super::Initialize(Owner);
}
