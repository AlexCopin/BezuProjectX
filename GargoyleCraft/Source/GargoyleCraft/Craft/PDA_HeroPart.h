#pragma once

#include "PDA_Recipe.h"
#include "PDA_HeroPart.generated.h"

UCLASS()
class GARGOYLECRAFT_API UPDA_HeroPart : public UPDA_Recipe
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	TObjectPtr<USkeletalMesh> PartMesh;
};
