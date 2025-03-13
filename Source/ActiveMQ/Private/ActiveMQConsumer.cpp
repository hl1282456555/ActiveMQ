// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveMQConsumer.h"

#include "ActiveMQExceptionHelper.h"
#include "Utils/ActiveMQMessageListener.h"

THIRD_PARTY_INCLUDES_START
#include "cms/MessageConsumer.h"
THIRD_PARTY_INCLUDES_END

void UActiveMQConsumer::BeginDestroy()
{
	UObject::BeginDestroy();

	if (InnerConsumer)
	{
		try
		{
			InnerConsumer->close();
		}
		catch (cms::CMSException&)
		{
			// ignore exception for automatic close
		}

		InnerConsumer.Reset();
	}
}

void UActiveMQConsumer::SetInnerConsumer(const TSharedPtr<cms::MessageConsumer>& NewConsumer)
{
	InnerConsumer = NewConsumer;
	if (InnerConsumer)
	{
		try
		{
			MessageListener = MakeShared<FActiveMQMessageListener>(this);
			InnerConsumer->setMessageListener(MessageListener.Get());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Consumer)
	}
}

const TSharedPtr<cms::MessageConsumer>& UActiveMQConsumer::GetInnerConsumer() const
{
	return InnerConsumer;
}

UActiveMQMessage* UActiveMQConsumer::Receive()
{
	UActiveMQMessage* Result = nullptr;

	UActiveMQSubsystem* Subsystem = GetWorld()->GetSubsystem<UActiveMQSubsystem>();
	if (InnerConsumer && Subsystem != nullptr)
	{
		try
		{
			Result = Subsystem->ConvertCMSMessageToUEMessage(this, InnerConsumer->receive());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Consumer)
	}

	return Result;
}

UActiveMQMessage* UActiveMQConsumer::Receive_WithTimeOut(int32 Millisecs)
{
	UActiveMQMessage* Result = nullptr;

	UActiveMQSubsystem* Subsystem = GetWorld()->GetSubsystem<UActiveMQSubsystem>();
	if (InnerConsumer && Subsystem != nullptr)
	{
		try
		{
			Result = Subsystem->ConvertCMSMessageToUEMessage(this, InnerConsumer->receive(Millisecs));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Consumer)
	}

	return Result;
}

UActiveMQMessage* UActiveMQConsumer::ReceiveNoWait()
{
	UActiveMQMessage* Result = nullptr;

	UActiveMQSubsystem* Subsystem = GetWorld()->GetSubsystem<UActiveMQSubsystem>();
	if (InnerConsumer && Subsystem != nullptr)
	{
		try
		{
			Result = Subsystem->ConvertCMSMessageToUEMessage(this, InnerConsumer->receiveNoWait());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Consumer)
	}

	return Result;
}

FString UActiveMQConsumer::GetMessageSelector() const
{
	if (InnerConsumer)
	{
		try
		{
			return UTF8_TO_TCHAR(InnerConsumer->getMessageSelector()->c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Consumer)
	}

	return TEXT("");
}

void UActiveMQConsumer::Start()
{
	if (InnerConsumer)
	{
		try
		{
			InnerConsumer->start();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Consumer)
	}
}

void UActiveMQConsumer::Close()
{
	if (InnerConsumer)
	{
		try
		{
			InnerConsumer->close();

			OnClosed.Broadcast(this);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Consumer)
	}
}

void UActiveMQConsumer::Stop()
{
	if (InnerConsumer)
	{
		try
		{
			InnerConsumer->stop();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Consumer)
	}
}
