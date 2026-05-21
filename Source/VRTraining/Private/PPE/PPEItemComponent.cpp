#include "PPE/PPEItemComponent.h"
#include "Training/TrainingSessionSubsystem.h"

UPPEItemComponent::UPPEItemComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPPEItemComponent::SelectItem()
{
    bSelected = true;

    if (GetWorld() && GetWorld()->GetGameInstance())
    {
        if (UTrainingSessionSubsystem* TrainingSession = GetWorld()->GetGameInstance()->GetSubsystem<UTrainingSessionSubsystem>())
        {
            FTrainingEventRecord Event;
            Event.EventType = bDamaged ? ETrainingEventType::DamagedPpeSelected : ETrainingEventType::PpeSelected;
            Event.Action = TEXT("ppe_selected");
            Event.HazardCode = ItemCode;
            Event.HazardCategory = TEXT("ppe");
            Event.bIsCorrect = IsValidSelection();
            TrainingSession->RecordTrainingEvent(Event);
        }
    }
}

void UPPEItemComponent::RejectItem()
{
    bSelected = false;

    if (GetWorld() && GetWorld()->GetGameInstance())
    {
        if (UTrainingSessionSubsystem* TrainingSession = GetWorld()->GetGameInstance()->GetSubsystem<UTrainingSessionSubsystem>())
        {
            FTrainingEventRecord Event;
            Event.EventType = ETrainingEventType::FeedbackShown;
            Event.Action = TEXT("ppe_rejected");
            Event.HazardCode = ItemCode;
            Event.HazardCategory = TEXT("ppe");
            Event.bIsCorrect = bDamaged;
            TrainingSession->RecordTrainingEvent(Event);
        }
    }
}

bool UPPEItemComponent::IsSelected() const
{
    return bSelected;
}

bool UPPEItemComponent::IsValidSelection() const
{
    return bRequired && !bDamaged;
}
