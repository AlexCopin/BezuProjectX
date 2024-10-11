#pragma once

#include "CoreMinimal.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GC_SaveSubsystem.generated.h"
/**
 *
 */

const FString FILE_NAME = "GargoyleCraft_Saves";

UCLASS()
class GARGOYLECRAFT_API UGC_SaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool SavePlayerData();

	UFUNCTION(BlueprintCallable)
	FPlayerData LoadPlayerData();
};