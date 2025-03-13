// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class ActiveMQ : ModuleRules
{
	public ActiveMQ(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp20;
		
		bUseRTTI = true;
		bEnableExceptions = true;

		string ThirdPartyPath = Path.Combine(ModuleDirectory, "../../ThirdParty/ActiveMQ-CMS");
		
		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ThirdPartyPath, "include")
			}
			);
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Projects",
				"OpenSSL"
				// ... add other public dependencies that you statically link with here ...
			}
			);

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.AddRange(new string[]
			{
				Path.Combine(ThirdPartyPath, "lib", "libapr-1.lib"),
				Path.Combine(ThirdPartyPath, "lib", "libaprapp-1.lib"),
				Path.Combine(ThirdPartyPath, "lib", "activemq-cpp.lib")
			});
				
			PublicDelayLoadDLLs.AddRange(new string[] {
				"libapr-1.dll",
				"activemq-cpp.dll",
			});
				
			RuntimeDependencies.Add(Path.Combine(ThirdPartyPath, "bin", "libapr-1.dll"));
			RuntimeDependencies.Add(Path.Combine(ThirdPartyPath, "bin", "activemq-cpp.dll"));
			
			PublicDefinitions.AddRange(new string[]
			{
				"NOMINMAX",
				"CMS_DLL",
				"AMQCPP_DLL",
				"DECAF_DLL",
				"HAVE_OPENSSL"
			});
		}
	}
}
