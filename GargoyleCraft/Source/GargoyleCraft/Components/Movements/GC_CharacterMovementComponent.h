#pragma once
#include "GameFramework/CharacterMovementComponent.h"

#include "GC_CharacterMovementComponent.generated.h"

UCLASS()
class UGC_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
    virtual void BeginPlay() override;

};