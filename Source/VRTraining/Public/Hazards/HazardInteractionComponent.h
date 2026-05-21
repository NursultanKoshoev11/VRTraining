#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Training/TrainingTypes.h"
#include "HazardInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHazardInteractionEvaluated, const FString&, HazardCode, bool, bWasCorrect);

UCLASS(ClassGroup=(Training), meta=(BlueprintSpawnableComponent))
class VRTRAINING_API UHazardInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHazardInteractionComponent();

    UFUNCTION(BlueprintCallable, Category = "Hazard")
    void MarkHazardFound(const FString& Action = TEXT("marked_hazard"));

    UFUNCTION(BlueprintCallable, Category = "Hazard")
    void MarkUnsafeAction(const FString& Action = TEXT("unsafe_action"));

    UFUNCTION(BlueprintPure, Category = "Hazard")
    bool IsResolved() const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
    FString HazardCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
    FString HazardCategory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
    EHazardSeverity Severity = EHazardSeverity::Minor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
    bool bCritical = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
    FString FeedbackLocalizationKey;

    UPROPERTY(BlueprintAssignable, Category = "Hazard")
    FOnHazardInteractionEvaluated OnHazardInteractionEvaluated;

private:
    bool bResolved = false;
};
