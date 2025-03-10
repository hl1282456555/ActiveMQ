// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveMQConnection.h"

#include <cms/Connection.h>

#include "ActiveMQExceptionHelper.h"
#include "ActiveMQSubsystem.h"

DECLARE_LOG_CATEGORY_CLASS(LogActiveMQConnection, Log, All);

FActiveMQConnectionMetaData::FActiveMQConnectionMetaData()
	: CMSMajorVersion(-1)
	, CMSMinorVersion(-1)
	, ProviderMajorVersion(-1)
	, ProviderMinorVersion(-1)
	, ProviderPatchVersion(-1)
{
}

UActiveMQConnection::UActiveMQConnection()
{
}

UActiveMQConnection::~UActiveMQConnection()
{
}

void UActiveMQConnection::BeginDestroy()
{
	UObject::BeginDestroy();

	if (InnerConnection)
	{
		try
		{
			InnerConnection->close();
		}
		catch (cms::CMSException&)
		{
			// ignore exception for automatic close
		}

		InnerConnection.Reset();
	}
}

void UActiveMQConnection::SetInnerConnection(const TSharedPtr<cms::Connection>& NewConnection)
{
	InnerConnection = NewConnection;
	if (InnerConnection)
	{
		InnerConnection->setExceptionListener(this);
	}
}

const TSharedPtr<cms::Connection>& UActiveMQConnection::GetInnerConnection() const
{
	return InnerConnection;
}

FString UActiveMQConnection::GetUsername() const
{
	return Username;
}

void UActiveMQConnection::SetUsername(const FString& InUsername)
{
	Username = InUsername;
}

FString UActiveMQConnection::GetPassword() const
{
	return Password;
}

void UActiveMQConnection::SetPassword(const FString& InPassword)
{
	Password = InPassword;
}

FActiveMQConnectionMetaData UActiveMQConnection::GetMetaData() const
{
	FActiveMQConnectionMetaData Result;
	if (!InnerConnection.IsValid())
	{
		return Result;
	}

	try
	{
		const cms::ConnectionMetaData* MetaData = InnerConnection->getMetaData();
		if (MetaData == nullptr)
		{
			return Result;
		}

		Result.CMSVersion = MetaData->getCMSVersion().c_str();
		Result.CMSMajorVersion = MetaData->getCMSMajorVersion();
		Result.CMSMinorVersion = MetaData->getCMSMinorVersion();
		Result.CMSProviderName = MetaData->getCMSProviderName().c_str();
		Result.ProviderVersion = MetaData->getProviderVersion().c_str();
		Result.ProviderMajorVersion = MetaData->getProviderMajorVersion();
		Result.ProviderMinorVersion = MetaData->getProviderMinorVersion();
		Result.ProviderPatchVersion = MetaData->getProviderPatchVersion();

		const std::vector<std::string>& PropertyNames = MetaData->getCMSXPropertyNames();
		for (const std::string& PropertyName : PropertyNames)
		{
			Result.CMSXPropertyNames.Add(FString(PropertyName.c_str()));
		}	
	}
	ACTIVEMQ_EXCEPTION_DELIVER_END(GetClientID(), EActiveMQExceptionOwnerType::EOT_Connection)

	return Result;
}

void UActiveMQConnection::Start()
{
	if (!InnerConnection.IsValid())
	{
		return;
	}

	try
	{
		InnerConnection->start();
	}
	ACTIVEMQ_EXCEPTION_DELIVER_END(GetClientID(), EActiveMQExceptionOwnerType::EOT_Connection)
}

void UActiveMQConnection::Close()
{
	if (!InnerConnection.IsValid())
	{
		return;
	}
	
	try
	{
		InnerConnection->close();

		OnConnectionClosed.Broadcast(this);
	}
	ACTIVEMQ_EXCEPTION_DELIVER_END(GetClientID(), EActiveMQExceptionOwnerType::EOT_Connection)
}

void UActiveMQConnection::Stop()
{
	if (!InnerConnection.IsValid())
	{
		return;
	}

	try
	{
		InnerConnection->stop();
	}
	ACTIVEMQ_EXCEPTION_DELIVER_END(GetClientID(), EActiveMQExceptionOwnerType::EOT_Connection)
}

UActiveMQSession* UActiveMQConnection::CreateSession(EActiveMQSessionAcknowledgeMode AcknowledgeMode)
{
	if (!InnerConnection.IsValid())
	{
		return nullptr;
	}

	try
	{
		TSharedPtr<cms::Session> InnerSession = MakeShareable(InnerConnection->createSession(static_cast<cms::Session::AcknowledgeMode>(AcknowledgeMode)));
		if (!InnerSession)
		{
			return nullptr;
		}

		UActiveMQSession* NewSession = NewObject<UActiveMQSession>(this);
		NewSession->SetInnerSession(InnerSession);

		return NewSession;
	}
	ACTIVEMQ_EXCEPTION_DELIVER_END(GetClientID(), EActiveMQExceptionOwnerType::EOT_Connection)

	return nullptr;
}

FString UActiveMQConnection::GetClientID() const
{
	if (!InnerConnection)
	{
		return TEXT("");
	}

	try
	{
		return FString(InnerConnection->getClientID().c_str());
	}
	ACTIVEMQ_EXCEPTION_DELIVER_END(GetClientID(), EActiveMQExceptionOwnerType::EOT_Connection)

	return TEXT("");
}

void UActiveMQConnection::SetClientID(const FString& InClientID)
{
	if (!InnerConnection)
	{
		return;
	}

	try
	{
		InnerConnection->setClientID(TCHAR_TO_UTF8(*InClientID));
	}
	ACTIVEMQ_EXCEPTION_DELIVER_END(GetClientID(), EActiveMQExceptionOwnerType::EOT_Connection)
}

void UActiveMQConnection::onException(const cms::CMSException& Exception)
{
	AsyncTask(ENamedThreads::Type::GameThread, [Exception, this]()
	{
		DeliverException(this, GetClientID(), EActiveMQExceptionOwnerType::EOT_Connection, Exception);
	});
}
