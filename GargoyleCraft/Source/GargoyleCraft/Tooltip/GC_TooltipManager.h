#pragma once

#include "CoreMinimal.h"
#include <GameplayEffect.h>
#include "GargoyleCraft/GameplayAbilitySystem/GC_AbilitySystemComponent.h"
#include "GC_TooltipManager.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FTooltipData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText Flavor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;

};

UCLASS()
class UGC_TooltipLibrary : public UBlueprintFunctionLibrary 
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FString ConstructGameplayEffectModifierInfos(const FGameplayModifierInfo& ModInfos);
	UFUNCTION(BlueprintCallable)
	static FTooltipData GetTooltipDataFromAbilitySystemComponent(UObject* WorldContext, UGC_AbilitySystemComponent*);
};