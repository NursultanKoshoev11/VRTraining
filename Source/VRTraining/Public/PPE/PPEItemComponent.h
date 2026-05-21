#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PPEItemComponent.generated.h"

UENUM(BlueprintType)
enum class EPPEItemType : uint8
{
    HardHat UMETA(DisplayName = "Hard Hat"),
    SafetyGlasses UMETA(DisplayName = "Safety Glasses"),
    Gloves UMETA(DisplayName = "Gloves"),
    HighVisibilityVest UMETA(DisplayName = "High Visibility Vest"),
    SafetyBoots UMETA(DisplayName = "Safety Boots"),
    Harness UMETA(DisplayName = "Harness")
};

UCLASS(ClassGroup=(Training), meta=(BlueprintSpawnableComponent))
class VRTRAINING_API UPPEItemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPPEItemComponent();

    UFUNCTION(BlueprintCallable, Category = "PPE")
    void SelectItem();

    UFUNCTION(BlueprintCallable, Category = "PPE")
    void RejectItem();

    UFUNCTION(BlueprintPure, Category = "PPE")
    bool IsSelected() const;

    UFUNCTION(BlueprintPure, Category = "PPE")
    bool IsValidSelection() const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PPE")
    EPPEItemType ItemType = EPPEItemType::HardHat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PPE")
    FString ItemCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PPE")
    bool bRequired = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PPE")
    bool bDamaged = false;

private:
    bool bSelected = false;
};
