// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GargoyleCraftEditor : ModuleRules
{
	public GargoyleCraftEditor(ReadOnlyTargetRules Target) : base(Target)
	{

        PublicIncludePaths.AddRange(
            new string[]
            {
                "GargoyleCraftEditor/public"
            });

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "GargoyleCraftEditor/private"
            });


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "GargoyleCraft",  "Core", "CoreUObject", "Engine"
            });
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UnrealEd"
            });

        PrivateIncludePathModuleNames.AddRange(
            new string[]
            {
            });

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
            });
    }
}
