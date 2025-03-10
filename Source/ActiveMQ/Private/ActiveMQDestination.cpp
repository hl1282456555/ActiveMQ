// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveMQDestination.h"

#include "ActiveMQExceptionHelper.h"

THIRD_PARTY_INCLUDES_START
#include "cms/Destination.h"
#include "cms/Topic.h"
#include "cms/Queue.h"
#include "cms/TemporaryQueue.h"
#include "cms/TemporaryTopic.h"
THIRD_PARTY_INCLUDES_END

#include "ActiveMQProperties.h"

UActiveMQDestination::UActiveMQDestination()
{
}

UActiveMQDestination::~UActiveMQDestination()
{
}

void UActiveMQDestination::BeginDestroy()
{
	UObject::BeginDestroy();
}

void UActiveMQDestination::SetInnerDestination(const TSharedPtr<cms::Destination>& NewDestination)
{
	InnerDestination = NewDestination;
}

const TSharedPtr<cms::Destination>& UActiveMQDestination::GetInnerDestination() const
{
	return InnerDestination;
}

EActiveMQDestinationType UActiveMQDestination::GetDestinationType() const
{
	return InnerDestination ? static_cast<EActiveMQDestinationType>(InnerDestination->getDestinationType()) : EActiveMQDestinationType::Queue;
}

UActiveMQDestination* UActiveMQDestination::Clone() const
{
	if (InnerDestination)
	{
		UActiveMQDestination* NewDestination = NewObject<UActiveMQDestination>(GetOuter());
    	NewDestination->InnerDestination = MakeShareable(InnerDestination->clone());	
	}

	return nullptr;
}

void UActiveMQDestination::Copy(UActiveMQDestination* Source)
{
	if (InnerDestination && Source->InnerDestination)
	{
		InnerDestination->copy(*Source->InnerDestination);
	}
}

bool UActiveMQDestination::Equals(UActiveMQDestination* Other) const
{
	return InnerDestination && Other->InnerDestination && InnerDestination->equals(*Other->InnerDestination);
}

UActiveMQProperties* UActiveMQDestination::GetProperties() const
{
	UActiveMQDestination* MutableThis = const_cast<UActiveMQDestination*>(this);
	UActiveMQProperties* NewProperties = NewObject<UActiveMQProperties>(MutableThis);
	NewProperties->SetInnerProperties(MakeShareable(InnerDestination->getCMSProperties().clone()));

	return NewProperties;
}

FString UActiveMQTopic::GetTopicName() const
{
	if (InnerDestination && InnerDestination->getDestinationType() == cms::Destination::TOPIC)
	{
		try
		{
			FString TopicName = UTF8_TO_TCHAR(StaticCastSharedPtr<cms::Topic>(InnerDestination)->getTopicName().c_str());
			return TopicName;
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Destination)
	}

	return TEXT("");
}

FString UActiveMQQueue::GetQueueName() const
{
	if (InnerDestination && InnerDestination->getDestinationType() == cms::Destination::QUEUE)
	{
		try
		{
			FString QueueName = UTF8_TO_TCHAR(StaticCastSharedPtr<cms::Queue>(InnerDestination)->getQueueName().c_str());
			return QueueName;
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Destination)
	}

	return TEXT("");
}

void UActiveMQTemporaryQueue::Destroy()
{
	if (InnerDestination && InnerDestination->getDestinationType() == cms::Destination::TEMPORARY_QUEUE)
	{
		try
		{
			StaticCastSharedPtr<cms::TemporaryQueue>(InnerDestination)->destroy();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Destination)
	}
}

void UActiveMQTemporaryTopic::Destroy()
{
	if (InnerDestination && InnerDestination->getDestinationType() == cms::Destination::TEMPORARY_TOPIC)
	{
		try
		{
			StaticCastSharedPtr<cms::TemporaryTopic>(InnerDestination)->destroy();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_Destination)
	}
}
