// Fill out your copyright notice in the Description page of Project Settings.


#include "PDA_GameData.h"

FAttributeDisplayData UPDA_GameData::FindAttributeDisplayValue(FGameplayAttribute Attribute)
{
		if(auto attributeData = AttributesDisplayValues->FindRow<FAttributeDisplayData>(*Attribute.GetName(), "Context"))
		{
			return *attributeData;
		}
    return FAttributeDisplayData();
}
