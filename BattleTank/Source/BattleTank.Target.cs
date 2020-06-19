// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BattleTankTarget : TargetRules
{
    public BattleTankTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;

        ExtraModuleNames.AddRange(new[] {"BattleTank"});
    }
}