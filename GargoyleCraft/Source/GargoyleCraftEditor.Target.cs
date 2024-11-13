// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GargoyleCraftEditorTarget : TargetRules
{
	public GargoyleCraftEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("GargoyleCraft");
        // Game editor
        ExtraModuleNames.AddRange(
            new string[]
            {
                "GargoyleCraftEditor"
            });
    }
}
