#pragma once

#include "CoreMinimal.h"
#include "ScenarioTypes.generated.h"

USTRUCT(BlueprintType)
struct FScenarioObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	FString ObjectiveCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	FString TitleLocalizationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario")
	bool bRequired = true;

	UPROPERTY(BlueprintReadOnly, Category = "Scenario")
	bool bCompleted = false;
};
