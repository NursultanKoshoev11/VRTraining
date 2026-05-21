#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Scenario/ScenarioTypes.h"
#include "ScenarioManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScenarioObjectiveChanged, const FString&, ObjectiveCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScenarioCompleted);

UCLASS(ClassGroup=(Training), meta=(BlueprintSpawnableComponent))
class DEFAULT_API UScenarioManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UScenarioManagerComponent();

	UFUNCTION(BlueprintCallable, Category = "Scenario")
	bool StartScenario(const FString& InModuleCode, const FString& InModuleVersion);

	UFUNCTION(BlueprintCallable, Category = "Scenario")
	bool CompleteObjective(const FString& ObjectiveCode);

	UFUNCTION(BlueprintPure, Category = "Scenario")
	bool CanCompleteScenario() const;

	UFUNCTION(BlueprintCallable, Category = "Scenario")
	bool CompleteScenario();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	FString ModuleCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	FString ModuleVersion = TEXT("1.0.0");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	TArray<FScenarioObjective> Objectives;

	UPROPERTY(BlueprintAssignable, Category = "Scenario")
	FOnScenarioObjectiveChanged OnScenarioObjectiveChanged;

	UPROPERTY(BlueprintAssignable, Category = "Scenario")
	FOnScenarioCompleted OnScenarioCompleted;

private:
	bool bScenarioStarted = false;
};
