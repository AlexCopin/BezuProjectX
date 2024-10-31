#pragma once

#include "CoreMinimal.h"
#include "GC_TooltipManager.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FTooltipData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Flavor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;

};

UCLASS()
class UGC_TooltipManager : public UObject 
{
	GENERATED_BODY()

};