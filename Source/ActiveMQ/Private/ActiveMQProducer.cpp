// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveMQProducer.h"

#include "ActiveMQDestination.h"
#include "ActiveMQExceptionHelper.h"
#include "Messages/ActiveMQMessage.h"

THIRD_PARTY_INCLUDES_START
#include "cms/MessageProducer.h"
THIRD_PARTY_INCLUDES_END

void UActiveMQProducer::BeginDestroy()
{
	UObject::BeginDestroy();

	if (InnerProducer)
	{
		try
		{
			InnerProducer->close();
		}
		catch (cms::CMSException&)
		{
			// ignore exception for automatic close
		}

		InnerProducer.Reset();
	}
}

void UActiveMQProducer::SetInnerProducer(const TSharedPtr<cms::MessageProducer>& NewProducer)
{
	InnerProducer = NewProducer;
}

const TSharedPtr<cms::MessageProducer>& UActiveMQProducer::GetInnerProducer() const
{
	return InnerProducer;
}

void UActiveMQProducer::Close()
{
	if (InnerProducer)
	{
		try
		{
			InnerProducer->close();
			OnClosed.Broadcast(this);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

void UActiveMQProducer::Send(UActiveMQMessage* Message)
{
	if (InnerProducer && IsValid(Message) && Message->GetInnerMessage())
	{
		try
		{
			InnerProducer->send(Message->GetInnerMessage().Get());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

void UActiveMQProducer::Send_WithParams(UActiveMQMessage* Message, EActiveMQDeliveryMode DeliveryMode, int32 Priority,
	int64 TimeToLive)
{
	if (InnerProducer && IsValid(Message) && Message->GetInnerMessage())
	{
		try
		{
			InnerProducer->send(Message->GetInnerMessage().Get(), static_cast<int32>(DeliveryMode), Priority, TimeToLive);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

void UActiveMQProducer::AsyncSend(UActiveMQMessage* Message)
{
	if (InnerProducer && IsValid(Message) && Message->GetInnerMessage())
	{
		try
		{
			InnerProducer->send(Message->GetInnerMessage().Get(), this);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

void UActiveMQProducer::AsyncSend_WithParams(UActiveMQMessage* Message, EActiveMQDeliveryMode DeliveryMode,
	int32 Priority, int64 TimeToLive)
{
	if (InnerProducer && IsValid(Message) && Message->GetInnerMessage())
	{
		try
		{
			InnerProducer->send(Message->GetInnerMessage().Get(), static_cast<int32>(DeliveryMode), Priority, TimeToLive, this);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

void UActiveMQProducer::SendTo(UActiveMQDestination* Destination, UActiveMQMessage* Message)
{
	if (InnerProducer && IsValid(Message) && Message->GetInnerMessage() && IsValid(Destination) && Destination->GetInnerDestination())
	{
		try
		{
			InnerProducer->send(Destination->GetInnerDestination().Get(), Message->GetInnerMessage().Get());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

void UActiveMQProducer::SendTo_WithParams(UActiveMQDestination* Destination, UActiveMQMessage* Message,
	EActiveMQDeliveryMode DeliveryMode, int32 Priority, int64 TimeToLive)
{
	if (InnerProducer && IsValid(Message) && Message->GetInnerMessage() && IsValid(Destination) && Destination->GetInnerDestination())
	{
		try
		{
			InnerProducer->send(Destination->GetInnerDestination().Get(), Message->GetInnerMessage().Get(), static_cast<int32>(DeliveryMode), Priority, TimeToLive);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

void UActiveMQProducer::AsyncSendTo(UActiveMQDestination* Destination, UActiveMQMessage* Message)
{
	if (InnerProducer && IsValid(Message) && Message->GetInnerMessage() && IsValid(Destination) && Destination->GetInnerDestination())
	{
		try
		{
			InnerProducer->send(Destination->GetInnerDestination().Get(), Message->GetInnerMessage().Get(), this);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

void UActiveMQProducer::AsyncSendTo_WithParams(UActiveMQDestination* Destination, UActiveMQMessage* Message,
	EActiveMQDeliveryMode DeliveryMode, int32 Priority, int64 TimeToLive)
{
	if (InnerProducer && IsValid(Message) && Message->GetInnerMessage() && IsValid(Destination) && Destination->GetInnerDestination())
	{
		try
		{
			InnerProducer->send(Destination->GetInnerDestination().Get(), Message->GetInnerMessage().Get(), static_cast<int32>(DeliveryMode), Priority, TimeToLive, this);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

void UActiveMQProducer::SetDeliveryMode(EActiveMQDeliveryMode Mode)
{
	if (InnerProducer)
	{
		try
		{
			InnerProducer->setDeliveryMode(static_cast<int32>(Mode));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

EActiveMQDeliveryMode UActiveMQProducer::GetDeliveryMode() const
{
	if (InnerProducer)
	{
		try
		{
			return static_cast<EActiveMQDeliveryMode>(InnerProducer->getDeliveryMode());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}

	return EActiveMQDeliveryMode::Persistent;
}

void UActiveMQProducer::SetDisableMessageID(bool bDisable)
{
	if (InnerProducer)
	{
		try
		{
			InnerProducer->setDisableMessageID(bDisable);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

bool UActiveMQProducer::GetDisableMessageID() const
{
	if (InnerProducer)
	{
		try
		{
			return InnerProducer->getDisableMessageID();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}

	return false;
}

void UActiveMQProducer::SetDisableMessageTimeStamp(bool bDisable)
{
	if (InnerProducer)
	{
		try
		{
			InnerProducer->setDisableMessageTimeStamp(bDisable);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

bool UActiveMQProducer::GetDisableMessageTimeStamp() const
{
	if (InnerProducer)
	{
		try
		{
			return InnerProducer->getDisableMessageTimeStamp();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}

	return false;
}

void UActiveMQProducer::SetPriority(int32 Priority)
{
	if (InnerProducer)
	{
		try
		{
			InnerProducer->setPriority(Priority);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

int32 UActiveMQProducer::GetPriority() const
{
	if (InnerProducer)
	{
		try
		{
			return InnerProducer->getPriority();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}

	return 0;
}

void UActiveMQProducer::SetTimeToLive(int64 Time)
{
	if (InnerProducer)
	{
		try
		{
			InnerProducer->setTimeToLive(Time);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}
}

int64 UActiveMQProducer::GetTimeToLive() const
{
	if (InnerProducer)
	{
		try
		{
			return InnerProducer->getTimeToLive();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Producer)
	}

	return 0;
}

void UActiveMQProducer::onSuccess()
{
	AsyncTask(ENamedThreads::Type::GameThread, [this](){ OnSendAsyncComplete.Broadcast(this, true); });
}

void UActiveMQProducer::onException(const cms::CMSException& Exception)
{
	AsyncTask(ENamedThreads::Type::GameThread, [this, Exception]()
	{
		OnSendAsyncComplete.Broadcast(this, false);
		DeliverException(this, GetName(), EActiveMQExceptionOwnerType::EOT_Producer, Exception);
	});
}
