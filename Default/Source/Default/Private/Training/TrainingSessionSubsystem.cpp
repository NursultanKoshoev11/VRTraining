#include "Training/TrainingSessionSubsystem.h"

bool UTrainingSessionSubsystem::StartTrainingSession(const FString& TraineeId, const FString& ModuleCode, const FString& ModuleVersion, const FString& DeviceId, const FString& AppVersion, const FString& Language)
{
	if (TraineeId.IsEmpty() || ModuleCode.IsEmpty() || ModuleVersion.IsEmpty() || DeviceId.IsEmpty())
	{
		return false;
	}

	CurrentSession = FTrainingSessionSummary();
	CurrentSession.ClientSessionId = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphensLower);
	CurrentSession.TraineeId = TraineeId;
	CurrentSession.ModuleCode = ModuleCode;
	CurrentSession.ModuleVersion = ModuleVersion;
	CurrentSession.DeviceId = DeviceId;
	CurrentSession.AppVersion = AppVersion;
	CurrentSession.Language = Language.IsEmpty() ? TEXT("en") : Language;
	CurrentSession.StartedAtUtc = FDateTime::UtcNow();
	CurrentSession.Status = ETrainingSessionStatus::InProgress;

	FTrainingEventRecord StartedEvent;
	StartedEvent.EventId = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphensLower);
	StartedEvent.EventType = ETrainingEventType::ModuleStarted;
	StartedEvent.ModuleCode = ModuleCode;
	StartedEvent.ModuleVersion = ModuleVersion;
	StartedEvent.bIsCorrect = true;
	StartedEvent.TimeOffsetSeconds = 0;
	CurrentSession.Events.Add(StartedEvent);

	BroadcastSessionUpdate();
	return true;
}

bool UTrainingSessionSubsystem::RecordTrainingEvent(const FTrainingEventRecord& EventRecord)
{
	if (CurrentSession.Status != ETrainingSessionStatus::InProgress)
	{
		return false;
	}

	FTrainingEventRecord NormalizedEvent = EventRecord;
	if (NormalizedEvent.EventId.IsEmpty())
	{
		NormalizedEvent.EventId = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphensLower);
	}
	if (NormalizedEvent.ModuleCode.IsEmpty())
	{
		NormalizedEvent.ModuleCode = CurrentSession.ModuleCode;
	}
	if (NormalizedEvent.ModuleVersion.IsEmpty())
	{
		NormalizedEvent.ModuleVersion = CurrentSession.ModuleVersion;
	}

	NormalizedEvent.TimeOffsetSeconds = CalculateCurrentTimeOffsetSeconds();
	CurrentSession.Events.Add(NormalizedEvent);

	switch (NormalizedEvent.EventType)
	{
	case ETrainingEventType::HazardFound:
		CurrentSession.HazardsFound++;
		break;
	case ETrainingEventType::HazardMissed:
		CurrentSession.HazardsMissed++;
		break;
	case ETrainingEventType::UnsafeAction:
		CurrentSession.UnsafeActions++;
		break;
	case ETrainingEventType::HintUsed:
		CurrentSession.HintsUsed++;
		break;
	default:
		break;
	}

	BroadcastSessionUpdate();
	return true;
}

bool UTrainingSessionSubsystem::CompleteTrainingSession()
{
	if (CurrentSession.Status != ETrainingSessionStatus::InProgress)
	{
		return false;
	}

	CurrentSession.CompletedAtUtc = FDateTime::UtcNow();
	CurrentSession.DurationSeconds = CalculateCurrentTimeOffsetSeconds();
	CurrentSession.Score = CalculateScore();
	CurrentSession.Status = ETrainingSessionStatus::Completed;

	FTrainingEventRecord CompletedEvent;
	CompletedEvent.EventId = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphensLower);
	CompletedEvent.EventType = ETrainingEventType::ModuleCompleted;
	CompletedEvent.ModuleCode = CurrentSession.ModuleCode;
	CompletedEvent.ModuleVersion = CurrentSession.ModuleVersion;
	CompletedEvent.bIsCorrect = true;
	CompletedEvent.TimeOffsetSeconds = CurrentSession.DurationSeconds;
	CurrentSession.Events.Add(CompletedEvent);

	BroadcastSessionUpdate();
	return true;
}

void UTrainingSessionSubsystem::MarkSessionPendingSync()
{
	if (CurrentSession.Status == ETrainingSessionStatus::Completed || CurrentSession.Status == ETrainingSessionStatus::Failed)
	{
		CurrentSession.Status = ETrainingSessionStatus::PendingSync;
		BroadcastSessionUpdate();
	}
}

void UTrainingSessionSubsystem::MarkSessionSynced(const FString& ServerSessionId)
{
	CurrentSession.ServerSessionId = ServerSessionId;
	CurrentSession.Status = ETrainingSessionStatus::Synced;
	BroadcastSessionUpdate();
}

void UTrainingSessionSubsystem::MarkSessionFailed()
{
	CurrentSession.Status = ETrainingSessionStatus::Failed;
	BroadcastSessionUpdate();
}

const FTrainingSessionSummary& UTrainingSessionSubsystem::GetCurrentSession() const
{
	return CurrentSession;
}

bool UTrainingSessionSubsystem::HasActiveSession() const
{
	return CurrentSession.Status == ETrainingSessionStatus::InProgress;
}

void UTrainingSessionSubsystem::BroadcastSessionUpdate()
{
	OnTrainingSessionUpdated.Broadcast(CurrentSession);
}

int32 UTrainingSessionSubsystem::CalculateScore() const
{
	int32 Score = 100;

	for (const FTrainingEventRecord& Event : CurrentSession.Events)
	{
		if (Event.EventType == ETrainingEventType::HazardMissed)
		{
			switch (Event.Severity)
			{
			case EHazardSeverity::Critical:
				Score -= 15;
				break;
			case EHazardSeverity::Medium:
				Score -= 8;
				break;
			case EHazardSeverity::Minor:
				Score -= 3;
				break;
			default:
				break;
			}
		}
		else if (Event.EventType == ETrainingEventType::UnsafeAction)
		{
			Score -= 20;
		}
		else if (Event.EventType == ETrainingEventType::HintUsed)
		{
			Score -= 5;
		}
	}

	return FMath::Clamp(Score, 0, 100);
}

int32 UTrainingSessionSubsystem::CalculateCurrentTimeOffsetSeconds() const
{
	if (CurrentSession.StartedAtUtc.GetTicks() == 0)
	{
		return 0;
	}

	return FMath::Max(0, static_cast<int32>((FDateTime::UtcNow() - CurrentSession.StartedAtUtc).GetTotalSeconds()));
}
