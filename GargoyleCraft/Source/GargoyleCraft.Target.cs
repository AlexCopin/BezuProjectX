// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GargoyleCraftTarget : TargetRules
{
	public GargoyleCraftTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("GargoyleCraft");
        if (bBuildEditor)
        {
            ExtraModuleNames.AddRange(
                new string[]
                {
                    "GargoyleCraftEditor"
                });
        }
    }
}
