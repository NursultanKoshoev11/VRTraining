#include "PPE/PPEItemComponent.h"
#include "Training/TrainingSessionSubsystem.h"

UPPEItemComponent::UPPEItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UPPEItemComponent::SelectItem()
{
	if (ItemCode.IsEmpty())
	{
		return false;
	}

	bSelected = true;
	bool bRecorded = false;

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
			bRecorded = TrainingSession->RecordTrainingEvent(Event);
		}
	}

	OnPPESelectionChanged.Broadcast(ItemCode, IsValidSelection());
	return bRecorded;
}

bool UPPEItemComponent::RejectItem()
{
	if (ItemCode.IsEmpty())
	{
		return false;
	}

	bSelected = false;
	bool bRecorded = false;

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
			bRecorded = TrainingSession->RecordTrainingEvent(Event);
		}
	}

	OnPPESelectionChanged.Broadcast(ItemCode, bDamaged);
	return bRecorded;
}

bool UPPEItemComponent::IsSelected() const
{
	return bSelected;
}

bool UPPEItemComponent::IsValidSelection() const
{
	return bRequired && !bDamaged;
}
