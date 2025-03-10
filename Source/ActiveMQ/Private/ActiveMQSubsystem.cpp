// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveMQSubsystem.h"
#include "ActiveMQ.h"

#include "ActiveMQConnection.h"

#include "Messages/ActiveMQTextMessage.h"
#include "Messages/ActiveMQMapMessage.h"
#include "Messages/ActiveMQBytesMessage.h"
#include "Messages/ActiveMQStreamMessage.h"
#include "Messages/ActiveMQObjectMessage.h"

THIRD_PARTY_INCLUDES_START
#include "cms/ConnectionFactory.h"
#include "cms/connection.h"
#include "cms/CMSException.h"
#include "cms/TextMessage.h"
#include "cms/MapMessage.h"
#include "cms/BytesMessage.h"
#include "cms/StreamMessage.h"
#include "cms/ObjectMessage.h"
THIRD_PARTY_INCLUDES_END

#include "ActiveMQDestination.h"

void UActiveMQSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UActiveMQSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

UActiveMQMessage* UActiveMQSubsystem::ConvertCMSMessageToUEMessage(UObject* Outer, cms::Message* InMessage)
{
	UActiveMQMessage* UEMessage = nullptr;
	if (cms::TextMessage* TextMessage = dynamic_cast<cms::TextMessage*>(InMessage))
	{
		UEMessage = NewObject<UActiveMQTextMessage>(Outer);
		UEMessage->SetInnerMessage(MakeShareable(TextMessage));
	}
	else if (cms::MapMessage* MapMessage = dynamic_cast<cms::MapMessage*>(InMessage))
	{
		UEMessage = NewObject<UActiveMQMapMessage>(Outer);
		UEMessage->SetInnerMessage(MakeShareable(MapMessage));
	}
	else if (cms::BytesMessage* BytesMessage = dynamic_cast<cms::BytesMessage*>(InMessage))
	{
		UEMessage = NewObject<UActiveMQBytesMessage>(Outer);
		UEMessage->SetInnerMessage(MakeShareable(BytesMessage));
	}
	else if (cms::StreamMessage* StreamMessage = dynamic_cast<cms::StreamMessage*>(InMessage))
	{
		UEMessage = NewObject<UActiveMQStreamMessage>(Outer);
		UEMessage->SetInnerMessage(MakeShareable(StreamMessage));
	}
	else if (cms::ObjectMessage* ObjectMessage = dynamic_cast<cms::ObjectMessage*>(InMessage))
	{
		UEMessage = NewObject<UActiveMQObjectMessage>(Outer);
		UEMessage->SetInnerMessage(MakeShareable(ObjectMessage));
	}

	return UEMessage;
}

UActiveMQConnection* UActiveMQSubsystem::CreateConnection(const FString& BrokerURI, const FString& Username, const FString& Password, const FString& ClientId)
{
	UActiveMQConnection* NewConnection = nullptr;

	try
	{
		TSharedPtr<cms::ConnectionFactory> ConnectionFactory(cms::ConnectionFactory::createCMSConnectionFactory(TCHAR_TO_UTF8(*BrokerURI)));

		if (cms::Connection* InnerConnection = ConnectionFactory->createConnection(TCHAR_TO_UTF8(*Username), TCHAR_TO_UTF8(*Password), TCHAR_TO_UTF8(*ClientId)))
		{
			NewConnection = NewObject<UActiveMQConnection>(this);
			NewConnection->SetInnerConnection(MakeShareable(InnerConnection));
		}
	}
	catch (cms::CMSException& Exception)
	{
		DispatchExceptionMessage(GetName(), EActiveMQExceptionOwnerType::EOT_Subsystem, UTF8_TO_TCHAR(Exception.what()));
	}

	return NewConnection;
}

bool UActiveMQSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UActiveMQSubsystem::DispatchExceptionMessage(const FString Owner, EActiveMQExceptionOwnerType OwnerType,
                                                  const FString& Message)
{
	FString OwnerTypeName;
	switch (OwnerType)
	{
	case EActiveMQExceptionOwnerType::EOT_Subsystem:
		OwnerTypeName = "ActiveMQ-Subsystem";
		break;
	case EActiveMQExceptionOwnerType::EOT_Connection:
		OwnerTypeName = "ActiveMQ-Connection";
		break;
	case EActiveMQExceptionOwnerType::EOT_Session:
		OwnerTypeName = "ActiveMQ-Session";
		break;
	case EActiveMQExceptionOwnerType::EOT_Destination:
		OwnerTypeName = "ActiveMQ-Destination";
		break;
	case EActiveMQExceptionOwnerType::EOT_Producer:
		OwnerTypeName = "ActiveMQ-Producer";
		break;
	case EActiveMQExceptionOwnerType::EOT_Consumer:
		OwnerTypeName = "ActiveMQ-Consumer";
		break;
	case EActiveMQExceptionOwnerType::EOT_Message:
		OwnerTypeName = "ActiveMQ-Message";
		break;
	default:
		OwnerTypeName = "Unknown";
		break;
	}
	
	UE_LOG(LogActiveMQ, Error, TEXT("[%s] Some error occurred, message: %s"), *OwnerTypeName, *Message);
	OnActiveMQThrowException.Broadcast(Owner, OwnerType, Message);
}
