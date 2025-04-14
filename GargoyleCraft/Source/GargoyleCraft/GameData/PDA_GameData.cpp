// Fill out your copyright notice in the Description page of Project Settings.


#include "PDA_GameData.h"

FAttributeDisplayData UPDA_GameData::FindAttributeDisplayValue(FGameplayAttribute Attribute)
{
		if(auto recipeData = AttributesDisplayValues->FindRow<FAttributeDisplayData>(*Attribute.GetName(), "Context"))
		{
			return *recipeData;
		}
    return FAttributeDisplayData();
}
