// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GC_Widget.generated.h"

/**
 *
 */
UCLASS()
class GARGOYLECRAFT_API UGC_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Refresh();
	virtual void Refresh_Implementation();

	virtual bool IsHovered() const override;
};