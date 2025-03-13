// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveMQQueueBrowser.h"

#include "ActiveMQDestination.h"
#include "ActiveMQExceptionHelper.h"
#include "Messages/ActiveMQMessageEnumeration.h"

THIRD_PARTY_INCLUDES_START
#include "cms/QueueBrowser.h"
#include "cms/Queue.h"
THIRD_PARTY_INCLUDES_END

void UActiveMQQueueBrowser::BeginDestroy()
{
	Super::BeginDestroy();

	if (InnerQueueBrowser)
	{
		try
		{
			InnerQueueBrowser->close();
		}
		catch (cms::CMSException&)
		{
			// ignore exception for automatic close
		}
	}
}

void UActiveMQQueueBrowser::SetInnerQueueBrowser(const TSharedPtr<cms::QueueBrowser>& NewQueueBrowser)
{
	InnerQueueBrowser = NewQueueBrowser;
}

const TSharedPtr<cms::QueueBrowser>& UActiveMQQueueBrowser::GetInnerQueueBrowser() const
{
	return InnerQueueBrowser;
}

void UActiveMQQueueBrowser::Close()
{
	if (InnerQueueBrowser)
	{
		try
		{
			InnerQueueBrowser->close();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_QueueBrowser)
	}
}

UActiveMQQueue* UActiveMQQueueBrowser::GetQueue() const
{
	UActiveMQQueue* NewQueue = nullptr;
	if (InnerQueueBrowser)
	{
		try
		{
			const cms::Queue* InnerQueue = InnerQueueBrowser->getQueue();
			if (InnerQueue != nullptr)
			{
				NewQueue = NewObject<UActiveMQQueue>(GetWorld());
				NewQueue->SetInnerDestination(MakeShareable(InnerQueue->clone()));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_QueueBrowser)
	}

	return NewQueue;
}

FString UActiveMQQueueBrowser::GetMessageSelector() const
{
	if (InnerQueueBrowser)
	{
		try
		{
			return UTF8_TO_TCHAR(InnerQueueBrowser->getMessageSelector()->c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_QueueBrowser)
	}

	return TEXT("");
}

UActiveMQMessageEnumeration* UActiveMQQueueBrowser::GetMessageEnumeration()
{
	UActiveMQMessageEnumeration* NewEnumeration = nullptr;
	if (InnerQueueBrowser)
	{
		try
		{
			cms::MessageEnumeration* InnerEnumeration = InnerQueueBrowser->getEnumeration();
			if (InnerEnumeration != nullptr)
			{
				NewEnumeration = NewObject<UActiveMQMessageEnumeration>(this);
				NewEnumeration->SetInnerEnumeration(MakeShareable(InnerEnumeration));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_QueueBrowser)
	}

	return NewEnumeration;
}
