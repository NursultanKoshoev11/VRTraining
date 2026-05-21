#include "Scenario/ScenarioManagerComponent.h"
#include "Training/TrainingSessionSubsystem.h"

UScenarioManagerComponent::UScenarioManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UScenarioManagerComponent::StartScenario(const FString& InModuleCode, const FString& InModuleVersion)
{
	if (InModuleCode.IsEmpty() || InModuleVersion.IsEmpty())
	{
		return false;
	}

	ModuleCode = InModuleCode;
	ModuleVersion = InModuleVersion;
	bScenarioStarted = true;

	for (FScenarioObjective& Objective : Objectives)
	{
		Objective.bCompleted = false;
	}

	return true;
}

bool UScenarioManagerComponent::CompleteObjective(const FString& ObjectiveCode)
{
	if (!bScenarioStarted || ObjectiveCode.IsEmpty())
	{
		return false;
	}

	for (FScenarioObjective& Objective : Objectives)
	{
		if (Objective.ObjectiveCode == ObjectiveCode)
		{
			Objective.bCompleted = true;
			OnScenarioObjectiveChanged.Broadcast(ObjectiveCode);

			if (GetWorld() && GetWorld()->GetGameInstance())
			{
				if (UTrainingSessionSubsystem* TrainingSession = GetWorld()->GetGameInstance()->GetSubsystem<UTrainingSessionSubsystem>())
				{
					FTrainingEventRecord Event;
					Event.EventType = ETrainingEventType::ChecklistItemCompleted;
					Event.ModuleCode = ModuleCode;
					Event.ModuleVersion = ModuleVersion;
					Event.Action = ObjectiveCode;
					Event.bIsCorrect = true;
					TrainingSession->RecordTrainingEvent(Event);
				}
			}

			return true;
		}
	}

	return false;
}

bool UScenarioManagerComponent::CanCompleteScenario() const
{
	if (!bScenarioStarted)
	{
		return false;
	}

	for (const FScenarioObjective& Objective : Objectives)
	{
		if (Objective.bRequired && !Objective.bCompleted)
		{
			return false;
		}
	}

	return true;
}

bool UScenarioManagerComponent::CompleteScenario()
{
	if (!CanCompleteScenario())
	{
		return false;
	}

	bScenarioStarted = false;
	OnScenarioCompleted.Broadcast();
	return true;
}
