// Copyright Epic Games, Inc. All Rights Reserved.

#include "ActiveMQ.h"
#include "Interfaces/IPluginManager.h"

THIRD_PARTY_INCLUDES_START
#include "activemq/library/ActiveMQCPP.h"
THIRD_PARTY_INCLUDES_END

#define LOCTEXT_NAMESPACE "FActiveMQModule"

DEFINE_LOG_CATEGORY(LogActiveMQ);

void FActiveMQModule::StartupModule()
{
	TSharedPtr<IPlugin> SelfPlugin = IPluginManager::Get().FindPlugin(TEXT("ActiveMQ"));
	if (!SelfPlugin.IsValid())
	{
		return;
	}

	FString DllFolder = FPaths::Combine(SelfPlugin->GetBaseDir(), TEXT("ThirdParty/ActiveMQ-CMS/bin"));

	AprHandle = FPlatformProcess::GetDllHandle(*FPaths::Combine(DllFolder, TEXT("libapr-1.dll")));
	ActiveMQHandle = FPlatformProcess::GetDllHandle(*FPaths::Combine(DllFolder, TEXT("activemq-cpp.dll")));

	if (AprHandle == nullptr || ActiveMQHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Active MQ dll could not be found"));
		return;
	}

	UE_LOG(LogActiveMQ, Log, TEXT("Initialized active mq library."));
	activemq::library::ActiveMQCPP::initializeLibrary();
}

void FActiveMQModule::ShutdownModule()
{
	if (AprHandle != nullptr && ActiveMQHandle != nullptr)
	{
		UE_LOG(LogActiveMQ, Log, TEXT("Shutdown active mq library."));
		activemq::library::ActiveMQCPP::shutdownLibrary();
	}
	
	if (AprHandle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(AprHandle);
		AprHandle = nullptr;
	}

	if (ActiveMQHandle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(ActiveMQHandle);
		ActiveMQHandle = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FActiveMQModule, ActiveMQ)