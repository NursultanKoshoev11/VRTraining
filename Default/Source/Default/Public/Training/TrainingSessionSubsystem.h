#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Training/TrainingTypes.h"
#include "TrainingSessionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTrainingSessionUpdated, const FTrainingSessionSummary&, SessionSummary);

UCLASS(BlueprintType)
class DEFAULT_API UTrainingSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Training")
	bool StartTrainingSession(const FString& TraineeId, const FString& ModuleCode, const FString& ModuleVersion, const FString& DeviceId, const FString& AppVersion, const FString& Language);

	UFUNCTION(BlueprintCallable, Category = "Training")
	bool RecordTrainingEvent(const FTrainingEventRecord& EventRecord);

	UFUNCTION(BlueprintCallable, Category = "Training")
	bool CompleteTrainingSession();

	UFUNCTION(BlueprintCallable, Category = "Training")
	void MarkSessionPendingSync();

	UFUNCTION(BlueprintCallable, Category = "Training")
	void MarkSessionSynced(const FString& ServerSessionId);

	UFUNCTION(BlueprintCallable, Category = "Training")
	void MarkSessionFailed();

	UFUNCTION(BlueprintPure, Category = "Training")
	const FTrainingSessionSummary& GetCurrentSession() const;

	UFUNCTION(BlueprintPure, Category = "Training")
	bool HasActiveSession() const;

	UPROPERTY(BlueprintAssignable, Category = "Training")
	FOnTrainingSessionUpdated OnTrainingSessionUpdated;

private:
	FTrainingSessionSummary CurrentSession;

	void BroadcastSessionUpdate();
	int32 CalculateScore() const;
	int32 CalculateCurrentTimeOffsetSeconds() const;
};
