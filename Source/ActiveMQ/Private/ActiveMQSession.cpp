// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveMQSession.h"

#include "ActiveMQConsumer.h"
#include "ActiveMQProducer.h"
#include "ActiveMQDestination.h"
#include "ActiveMQSubsystem.h"
#include "ActiveMQQueueBrowser.h"

#include "Messages/ActiveMQMessage.h"
#include "Messages/ActiveMQBytesMessage.h"
#include "Messages/ActiveMQMapMessage.h"
#include "Messages/ActiveMQStreamMessage.h"
#include "Messages/ActiveMQTextMessage.h"

THIRD_PARTY_INCLUDES_START
#include "cms/Session.h"
#include "cms/Queue.h"
THIRD_PARTY_INCLUDES_END

UActiveMQSession::UActiveMQSession()
{
	SessionID = FString::Printf(TEXT("ActiveMQSession_%s"), *FGuid::NewGuid().ToString());
}

UActiveMQSession::~UActiveMQSession()
{
}

void UActiveMQSession::BeginDestroy()
{
	UObject::BeginDestroy();

	if (InnerSession)
	{
		try
		{
			InnerSession->close();
		}
		catch (cms::CMSException&)
		{
			// ignore exception for automatic close
		}

		InnerSession.Reset();
	}
}

void UActiveMQSession::SetInnerSession(const TSharedPtr<cms::Session>& InSession)
{
	InnerSession = InSession;
}

const TSharedPtr<cms::Session>& UActiveMQSession::GetInnerSession() const
{
	return InnerSession;
}

FString UActiveMQSession::GetSessionID() const
{
	return SessionID;
}

void UActiveMQSession::SetSessionID(const FString& InSessionID)
{
	SessionID = InSessionID;
}

void UActiveMQSession::Start()
{
	if (InnerSession.IsValid())
	{
		try
		{
			InnerSession->start();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}
}

void UActiveMQSession::Close()
{
	if (InnerSession.IsValid())
	{
		try
		{
			InnerSession->close();
			OnClosed.Broadcast(this);

			Consumers.Empty();
			Producers.Empty();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}
}

void UActiveMQSession::Stop()
{
	if (InnerSession.IsValid())
	{
		try
		{
			InnerSession->stop();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}
}

void UActiveMQSession::Commit()
{
	if (InnerSession.IsValid())
	{
		try
		{
			InnerSession->commit();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}
}

void UActiveMQSession::Rollback()
{
	if (InnerSession.IsValid())
	{
		try
		{
			InnerSession->rollback();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}
}

void UActiveMQSession::Recover()
{
	if (InnerSession.IsValid())
	{
		try
		{
			InnerSession->recover();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}
}

UActiveMQConsumer* UActiveMQSession::CreateConsumer(UActiveMQDestination* Destination, const FString& Selector,
	bool bNoLocal)
{
	UActiveMQConsumer* NewConsumer = nullptr;
	if (InnerSession.IsValid())
	{
		try
		{
			cms::MessageConsumer* InnerConsumer = InnerSession->createConsumer(Destination->GetInnerDestination().Get(), TCHAR_TO_UTF8(*Selector), bNoLocal);
			if (InnerConsumer != nullptr)
			{
				NewConsumer = NewObject<UActiveMQConsumer>(this);
				NewConsumer->SetInnerConsumer(MakeShareable(InnerConsumer));
				NewConsumer->OnClosed.AddDynamic(this, &ThisClass::HandleConsumerCloseEvent);
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewConsumer;
}

UActiveMQConsumer* UActiveMQSession::CreateDurableConsumer(UActiveMQTopic* Topic, const FString& Name,
	const FString& Selector, bool bNoLocal)
{
	UActiveMQConsumer* NewConsumer = nullptr;
	if (InnerSession.IsValid())
	{
		try
		{
			if (cms::Topic* InnerTopic = dynamic_cast<cms::Topic*>(Topic->GetInnerDestination().Get()))
			{
				cms::MessageConsumer* InnerConsumer = InnerSession->createDurableConsumer(InnerTopic, TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*Selector), bNoLocal);
				if (InnerConsumer != nullptr)
				{
					NewConsumer = NewObject<UActiveMQConsumer>(this);
					NewConsumer->SetInnerConsumer(MakeShareable(InnerConsumer));
					NewConsumer->OnClosed.AddDynamic(this, &ThisClass::HandleConsumerCloseEvent);
				}	
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}
	
	return NewConsumer;
}

UActiveMQProducer* UActiveMQSession::CreateProducer(UActiveMQDestination* Destination)
{
	UActiveMQProducer* NewProducer = nullptr;
	if (InnerSession.IsValid())
	{
		try
		{
			cms::Destination* InnerDestination = nullptr;
			if (IsValid(Destination) && Destination->GetInnerDestination())
			{
				InnerDestination = Destination->GetInnerDestination().Get();
			}
			
			cms::MessageProducer* InnerProducer = InnerSession->createProducer(InnerDestination);
			if (InnerProducer != nullptr)
			{
				NewProducer = NewObject<UActiveMQProducer>(this);
				NewProducer->SetInnerProducer(MakeShareable(InnerProducer));
				NewProducer->OnClosed.AddDynamic(this, &ThisClass::HandleProducerCloseEvent);
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewProducer;
}

UActiveMQQueueBrowser* UActiveMQSession::CreateBrowser(UActiveMQQueue* Queue, const FString& Selector)
{
	UActiveMQQueueBrowser* NewBrowser = nullptr;
	if (InnerSession && IsValid(Queue))
	{
		try
		{
			if (cms::Queue* InnerQueue = dynamic_cast<cms::Queue*>(Queue->GetInnerDestination().Get()))
			{
				cms::QueueBrowser* InnerBrowser = InnerSession->createBrowser(InnerQueue, TCHAR_TO_UTF8(*Selector));
				if (InnerBrowser != nullptr)
				{
					NewBrowser = NewObject<UActiveMQQueueBrowser>(this);
					NewBrowser->SetInnerQueueBrowser(MakeShareable(InnerBrowser));
				}
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewBrowser;
}

UActiveMQQueue* UActiveMQSession::CreateQueue(const FString& QueueName)
{
	UActiveMQQueue* NewQueue = nullptr;
	if (InnerSession)
	{
		try
		{
			if (cms::Queue* InnerQueue = InnerSession->createQueue(TCHAR_TO_UTF8(*QueueName)))
			{
				NewQueue = NewObject<UActiveMQQueue>(this);
				NewQueue->SetInnerDestination(MakeShareable(InnerQueue));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewQueue;
}

UActiveMQTopic* UActiveMQSession::CreateTopic(const FString& TopicName)
{
	UActiveMQTopic* NewTopic = nullptr;
	if (InnerSession)
	{
		try
		{
			if (cms::Topic* InnerTopic = InnerSession->createTopic(TCHAR_TO_UTF8(*TopicName)))
			{
				NewTopic = NewObject<UActiveMQTopic>(this);
				NewTopic->SetInnerDestination(MakeShareable(InnerTopic));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewTopic;
}

UActiveMQTemporaryQueue* UActiveMQSession::CreateTemporaryQueue()
{
	UActiveMQTemporaryQueue* NewQueue = nullptr;
	if (InnerSession)
	{
		try
		{
			if (cms::TemporaryQueue* InnerQueue = InnerSession->createTemporaryQueue())
			{
				NewQueue = NewObject<UActiveMQTemporaryQueue>(this);
				NewQueue->SetInnerDestination(MakeShareable(InnerQueue));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewQueue;
}

UActiveMQTemporaryTopic* UActiveMQSession::CreateTemporaryTopic()
{
	UActiveMQTemporaryTopic* NewTopic = nullptr;
	if (InnerSession)
	{
		try
		{
			if (cms::TemporaryTopic* InnerTopic = InnerSession->createTemporaryTopic())
			{
				NewTopic = NewObject<UActiveMQTemporaryTopic>(this);
				NewTopic->SetInnerDestination(MakeShareable(InnerTopic));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewTopic;
}

UActiveMQMessage* UActiveMQSession::CreateMessage()
{
	UActiveMQMessage* NewMessage = nullptr;
	if (InnerSession)
	{
		try
		{
			if (cms::Message* InnerMessage = InnerSession->createMessage())
			{
				NewMessage = NewObject<UActiveMQMessage>(this);
				NewMessage->SetInnerMessage(MakeShareable(InnerMessage));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewMessage;
}

UActiveMQBytesMessage* UActiveMQSession::CreateBytesMessage(const TArray<uint8>& Bytes)
{
	UActiveMQBytesMessage* NewMessage = nullptr;
	if (InnerSession)
	{
		try
		{
			cms::BytesMessage* InnerMessage = nullptr;
			if (Bytes.IsEmpty())
			{
				InnerMessage = InnerSession->createBytesMessage();
			}
			else
			{
				InnerMessage = InnerSession->createBytesMessage(Bytes.GetData(), Bytes.Num());
			}

			if (InnerMessage)
			{
				NewMessage = NewObject<UActiveMQBytesMessage>(this);
				NewMessage->SetInnerMessage(MakeShareable(InnerMessage));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewMessage;
}

UActiveMQStreamMessage* UActiveMQSession::CreateStreamMessage()
{
	UActiveMQStreamMessage* NewMessage = nullptr;
	if (InnerSession)
	{
		try
		{
			if (cms::StreamMessage* InnerMessage = InnerSession->createStreamMessage())
			{
				NewMessage = NewObject<UActiveMQStreamMessage>(this);
				NewMessage->SetInnerMessage(MakeShareable(InnerMessage));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewMessage;
}

UActiveMQTextMessage* UActiveMQSession::CreateTextMessage(const FString& Text)
{
	UActiveMQTextMessage* NewMessage = nullptr;
	if (InnerSession)
	{
		try
		{
			cms::TextMessage* InnerMessage = nullptr;
			if (Text.IsEmpty())
			{
				InnerMessage = InnerSession->createTextMessage();
			}
			else
			{
				InnerMessage = InnerSession->createTextMessage(TCHAR_TO_UTF8(*Text));
			}

			if (InnerMessage != nullptr)
			{
				NewMessage = NewObject<UActiveMQTextMessage>(this);
				NewMessage->SetInnerMessage(MakeShareable(InnerMessage));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewMessage;
}

UActiveMQMapMessage* UActiveMQSession::CreateMapMessage()
{
	UActiveMQMapMessage* NewMessage = nullptr;
	if (InnerSession)
	{
		try
		{
			if (cms::Message* InnerMessage = InnerSession->createMapMessage())
			{
				NewMessage = NewObject<UActiveMQMapMessage>(this);
				NewMessage->SetInnerMessage(MakeShareable(InnerMessage));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return NewMessage;
}

EActiveMQSessionAcknowledgeMode UActiveMQSession::GetAcknowledgeMode() const
{
	if (InnerSession)
	{
		try
		{
			return static_cast<EActiveMQSessionAcknowledgeMode>(InnerSession->getAcknowledgeMode());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return EActiveMQSessionAcknowledgeMode::AUTO_ACKNOWLEDGE;
}

bool UActiveMQSession::IsTransacted() const
{
	if (InnerSession)
	{
		try
		{
			return InnerSession->isTransacted();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}

	return false;
}

void UActiveMQSession::Unsubscribe(const FString& Name)
{
	if (InnerSession)
	{
		try
		{
			InnerSession->unsubscribe(TCHAR_TO_UTF8(*Name));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(SessionID, EActiveMQExceptionOwnerType::EOT_Session)
	}
}

void UActiveMQSession::HandleConsumerCloseEvent(UActiveMQConsumer* Consumer)
{
	Consumers.Remove(Consumer);
}

void UActiveMQSession::HandleProducerCloseEvent(UActiveMQProducer* Producer)
{
	Producers.Remove(Producer);
}
