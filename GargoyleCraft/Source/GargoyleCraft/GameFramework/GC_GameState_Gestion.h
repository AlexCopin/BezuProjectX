#pragma once


#include "GameFramework/GameState.h"
#include "GC_GameState_Gestion.generated.h"

class UPDA_GameData;

UCLASS()
class GARGOYLECRAFT_API AGC_GameState_Gestion : public AGameState
{
  GENERATED_BODY()
public:

  virtual void BeginPlay() override;

  UPROPERTY(EditAnywhere,BlueprintReadWrite)
  TObjectPtr<UPDA_GameData> DefaultGameData;
};