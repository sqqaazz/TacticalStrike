// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TacticalStrikeTarget : TargetRules
{
	public TacticalStrikeTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        //DefaultBuildSettings = BuildSettingsVersion.V2;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        //IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.AddRange( new string[] { "TacticalStrike" } );
	}
}
