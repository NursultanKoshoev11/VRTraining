#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Training/TrainingTypes.h"
#include "TrainingSessionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTrainingSessionUpdated, const FTrainingSessionSummary&, SessionSummary);

UCLASS(BlueprintType)
class VRTRAINING_API UTrainingSessionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Training")
    void StartTrainingSession(const FString& TraineeId, const FString& ModuleCode, const FString& ModuleVersion, const FString& DeviceId, const FString& AppVersion, const FString& Language);

    UFUNCTION(BlueprintCallable, Category = "Training")
    void RecordTrainingEvent(const FTrainingEventRecord& EventRecord);

    UFUNCTION(BlueprintCallable, Category = "Training")
    void CompleteTrainingSession();

    UFUNCTION(BlueprintCallable, Category = "Training")
    void MarkSessionPendingSync();

    UFUNCTION(BlueprintCallable, Category = "Training")
    void MarkSessionSynced(const FString& ServerSessionId);

    UFUNCTION(BlueprintPure, Category = "Training")
    const FTrainingSessionSummary& GetCurrentSession() const;

    UPROPERTY(BlueprintAssignable, Category = "Training")
    FOnTrainingSessionUpdated OnTrainingSessionUpdated;

private:
    FTrainingSessionSummary CurrentSession;
    FDateTime SessionStartedAt;

    void BroadcastSessionUpdate();
    int32 CalculateScore() const;
};
