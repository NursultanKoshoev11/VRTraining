#include "Hazards/HazardInteractionComponent.h"
#include "Training/TrainingSessionSubsystem.h"

UHazardInteractionComponent::UHazardInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UHazardInteractionComponent::MarkHazardFound(const FString& Action)
{
	if (bResolved || HazardCode.IsEmpty())
	{
		return false;
	}

	bResolved = true;
	bool bRecorded = false;

	if (GetWorld() && GetWorld()->GetGameInstance())
	{
		if (UTrainingSessionSubsystem* TrainingSession = GetWorld()->GetGameInstance()->GetSubsystem<UTrainingSessionSubsystem>())
		{
			FTrainingEventRecord Event;
			Event.EventType = ETrainingEventType::HazardFound;
			Event.HazardCode = HazardCode;
			Event.HazardCategory = HazardCategory;
			Event.Severity = Severity;
			Event.Action = Action;
			Event.bIsCorrect = true;
			bRecorded = TrainingSession->RecordTrainingEvent(Event);
		}
	}

	OnHazardInteractionEvaluated.Broadcast(HazardCode, bRecorded);
	return bRecorded;
}

bool UHazardInteractionComponent::RecordUnsafeTrainingAction(const FString& Action)
{
	if (HazardCode.IsEmpty())
	{
		return false;
	}

	bool bRecorded = false;

	if (GetWorld() && GetWorld()->GetGameInstance())
	{
		if (UTrainingSessionSubsystem* TrainingSession = GetWorld()->GetGameInstance()->GetSubsystem<UTrainingSessionSubsystem>())
		{
			FTrainingEventRecord Event;
			Event.EventType = ETrainingEventType::UnsafeAction;
			Event.HazardCode = HazardCode;
			Event.HazardCategory = HazardCategory;
			Event.Severity = Severity;
			Event.Action = Action;
			Event.bIsCorrect = false;
			bRecorded = TrainingSession->RecordTrainingEvent(Event);
		}
	}

	OnHazardInteractionEvaluated.Broadcast(HazardCode, false);
	return bRecorded;
}

bool UHazardInteractionComponent::IsResolved() const
{
	return bResolved;
}
