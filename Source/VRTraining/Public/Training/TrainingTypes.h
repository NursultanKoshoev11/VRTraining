#pragma once

#include "CoreMinimal.h"
#include "TrainingTypes.generated.h"

UENUM(BlueprintType)
enum class ETrainingSessionStatus : uint8
{
    NotStarted UMETA(DisplayName = "Not Started"),
    InProgress UMETA(DisplayName = "In Progress"),
    Completed UMETA(DisplayName = "Completed"),
    Failed UMETA(DisplayName = "Failed"),
    PendingSync UMETA(DisplayName = "Pending Sync"),
    Synced UMETA(DisplayName = "Synced")
};

UENUM(BlueprintType)
enum class ETrainingEventType : uint8
{
    ModuleStarted UMETA(DisplayName = "Module Started"),
    ModuleCompleted UMETA(DisplayName = "Module Completed"),
    HazardFound UMETA(DisplayName = "Hazard Found"),
    HazardMissed UMETA(DisplayName = "Hazard Missed"),
    UnsafeAction UMETA(DisplayName = "Unsafe Action"),
    PpeSelected UMETA(DisplayName = "PPE Selected"),
    DamagedPpeSelected UMETA(DisplayName = "Damaged PPE Selected"),
    ChecklistItemCompleted UMETA(DisplayName = "Checklist Item Completed"),
    HintUsed UMETA(DisplayName = "Hint Used"),
    FeedbackShown UMETA(DisplayName = "Feedback Shown")
};

UENUM(BlueprintType)
enum class EHazardSeverity : uint8
{
    Minor UMETA(DisplayName = "Minor"),
    Medium UMETA(DisplayName = "Medium"),
    Critical UMETA(DisplayName = "Critical")
};

USTRUCT(BlueprintType)
struct FTrainingEventRecord
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString EventId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    ETrainingEventType EventType = ETrainingEventType::ModuleStarted;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString ModuleCode;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString ModuleVersion;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString HazardCode;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString HazardCategory;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    EHazardSeverity Severity = EHazardSeverity::Minor;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString Action;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    bool bIsCorrect = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    int32 TimeOffsetSeconds = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString MetadataJson;
};

USTRUCT(BlueprintType)
struct FTrainingSessionSummary
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString ClientSessionId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString ServerSessionId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString TraineeId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString ModuleCode;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString ModuleVersion;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString DeviceId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString AppVersion;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    FString Language;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    int32 DurationSeconds = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    int32 Score = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    int32 HazardsFound = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    int32 HazardsMissed = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    int32 UnsafeActions = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    int32 HintsUsed = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    ETrainingSessionStatus Status = ETrainingSessionStatus::NotStarted;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Training")
    TArray<FTrainingEventRecord> Events;
};
