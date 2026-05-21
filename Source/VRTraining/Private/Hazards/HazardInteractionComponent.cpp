#include "Hazards/HazardInteractionComponent.h"
#include "Training/TrainingSessionSubsystem.h"

UHazardInteractionComponent::UHazardInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHazardInteractionComponent::MarkHazardFound(const FString& Action)
{
    if (bResolved)
    {
        return;
    }

    bResolved = true;

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
            TrainingSession->RecordTrainingEvent(Event);
        }
    }

    OnHazardInteractionEvaluated.Broadcast(HazardCode, true);
}

void UHazardInteractionComponent::MarkUnsafeAction(const FString& Action)
{
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
            TrainingSession->RecordTrainingEvent(Event);
        }
    }

    OnHazardInteractionEvaluated.Broadcast(HazardCode, false);
}

bool UHazardInteractionComponent::IsResolved() const
{
    return bResolved;
}
