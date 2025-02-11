#pragma once

#include "GargoyleCraft/DataAssets/PDA_Generic.h"
#include "GargoyleCraft/DataAssets/PDA_Improvement.h"
#include "GameplayTagContainer.h"
#include "PDA_Blueprint.generated.h"

UCLASS()
class GARGOYLECRAFT_API UPDA_Blueprint : public UPDA_Generic
{
	GENERATED_BODY()
public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Improvement")
	TObjectPtr<UPDA_Improvement> Improvement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources")
	TMap<FGameplayTag, int> ResourcesRequired;

	virtual FTooltipData GetTooltip_Implementation() override;
};
