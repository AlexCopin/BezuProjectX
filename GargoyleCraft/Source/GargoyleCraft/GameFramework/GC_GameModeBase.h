#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "GC_GameModeBase.generated.h"

class UPDA_GameData;

/**
 *
 */
UCLASS()
class GARGOYLECRAFT_API AGC_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPDA_GameData> DefaultGameData;
};