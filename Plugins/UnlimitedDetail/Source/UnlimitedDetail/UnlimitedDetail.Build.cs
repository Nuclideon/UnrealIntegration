// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class UnlimitedDetail : ModuleRules
{
	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../UnlimitedDetailThirdParty/")); }
	}
	
	public string ProjectDirectory
	{
		get
		{
			return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../../"));
		}
	}

	private void CopyToTargetBinaries(string FilePathName, string TargetPathName, ReadOnlyTargetRules Target)
	{
		string BineriesDirectory = Path.Combine(TargetPathName, "Binaries", Target.Platform.ToString());
		string Filename = Path.GetFileName(FilePathName);

		if (!Directory.Exists(BineriesDirectory))
		{
			Directory.CreateDirectory(BineriesDirectory);
		}

		string FileFullName = Path.Combine(BineriesDirectory, Filename);
		if (!File.Exists(FileFullName))
		{
			File.Copy(FilePathName, FileFullName, true);
		}

		RuntimeDependencies.Add(FileFullName);
	}
	
	public UnlimitedDetail(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
		);
				

		PrivateIncludePaths.AddRange(
				new string[] {
					//required for FPostProcessMaterialInputs
					EngineDirectory + "/Source/Runtime/Renderer/Private",
					//required for OverridePassSequence.h (moved in UE5.5+)
					EngineDirectory + "/Source/Runtime/Renderer/Internal",
					"UnlimitedDetail/Public",
			}
		);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"RenderCore",
				"RHI",
				"Renderer",
				"Projects",
				"JsonUtilities",
				"Json",
				"HTTP",
				"DeveloperSettings"
				// ... add other public dependencies that you statically link with here ...
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Renderer",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);

		if (Target.Type != TargetRules.TargetType.Server)
		{
			PrivateDependencyModuleNames.AddRange(new string[] {
				"UMG",
		   });
		}

		string IncludePath = Path.Combine(ThirdPartyPath, "include");
		PublicIncludePaths.Add(IncludePath);

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			string LibPath = Path.Combine(ThirdPartyPath, "lib", "win_x64");

			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "udSDK.lib"));

			// Delay-load so the plugin can provide its own load path before
			// Windows tries to resolve the DLL at startup.
			PublicDelayLoadDLLs.Add("udSDK.dll");

			CopyToTargetBinaries(Path.Combine(LibPath, "udSDK.dll"), ProjectDirectory, Target);
			CopyToTargetBinaries(Path.Combine(LibPath, "udSDK.dll"), PluginDirectory, Target);
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string LibPath = Path.Combine(ThirdPartyPath, "lib", "ubuntu25.10_GCC_x64");
			string SoFile  = Path.Combine(LibPath, "libudSDK.so");

			// The .so serves as both import library and runtime binary on Linux.
			PublicAdditionalLibraries.Add(SoFile);

			// Tell the packager to bundle it.
			RuntimeDependencies.Add(SoFile);

			// Copy into Binaries/Linux/ so the Editor and cooked game can find
			// it via the $ORIGIN rpath that UE sets on its own binaries.
			CopyToTargetBinaries(SoFile, ProjectDirectory, Target);
			CopyToTargetBinaries(SoFile, PluginDirectory, Target);
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			// *** NOT YET AVAILABLE ***
			// The file in lib/osx_x64/ is a .dmg disk image, not a usable .dylib.
			// Mount it (double-click or: hdiutil attach udSDK.dmg), copy the
			// .dylib or .framework out, then fill in this block.
			//
			// For a plain .dylib once available:
			//   string LibPath   = Path.Combine(ThirdPartyPath, "lib", "osx_x64");
			//   string DylibFile = Path.Combine(LibPath, "libudSDK.dylib");
			//   PublicAdditionalLibraries.Add(DylibFile);
			//   RuntimeDependencies.Add(DylibFile);
			//   CopyToTargetBinaries(DylibFile, ProjectDirectory, Target);
			//   CopyToTargetBinaries(DylibFile, PluginDirectory, Target);
			throw new BuildException(
				"udSDK macOS support is not yet configured. " +
				"A usable .dylib has not been extracted from the supplied .dmg. " +
				"See UnlimitedDetail.Build.cs for instructions.");
		}
	}
}
