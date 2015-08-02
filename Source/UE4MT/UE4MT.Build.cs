// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UE4MT : ModuleRules
{
	public UE4MT(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "AIModule" 
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });


        //PrivateIncludePaths.AddRange(
        //    new string[] {
        //        "UE4MT/Actors",
        //        "UE4MT/Actors/GameCharacter",
        //        "UE4MT/Actors/GameCharacter/Components",
        //        "UE4MT/Actors/GameCharacter/Controllers",
        //        "UE4MT/Actors/PlayerPawn",
        //        "UE4MT/Actors/PlayerPawn/Controllers",
        //        "UE4MT/Actors/PlayerPawn/Camera",
        //        "UE4MT/Generic",
        //        "UE4MT/Player",
        //        
		//	});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }
	}
}
