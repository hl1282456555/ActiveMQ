// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/ActiveMQMessageListener.h"

#include "ActiveMQConsumer.h"
#include "ActiveMQSubsystem.h"

THIRD_PARTY_INCLUDES_START
#include "cms/Message.h"
THIRD_PARTY_INCLUDES_END

FActiveMQMessageListener::FActiveMQMessageListener(const TWeakObjectPtr<UActiveMQConsumer>& InConsumer)
	: Consumer(InConsumer)
{
}

FActiveMQMessageListener::~FActiveMQMessageListener()
{
	Consumer.Reset();
}

void FActiveMQMessageListener::onMessage(const cms::Message* Message)
{
	cms::Message* ClonedMessage = Message->clone();
	AsyncTask(ENamedThreads::Type::GameThread, [this, ClonedMessage]()
	{
		if (!Consumer.IsValid())
		{
			delete ClonedMessage;
			return;
		}

		UActiveMQSubsystem* Subsystem = Consumer->GetWorld()->GetSubsystem<UActiveMQSubsystem>();
		if (Consumer->OnReceivedMessage.IsBound() && Subsystem != nullptr)
		{
			UActiveMQMessage* UEMessage = Subsystem->ConvertCMSMessageToUEMessage(Consumer.Get(), ClonedMessage);
			if (UEMessage != nullptr)
			{
				Consumer->OnReceivedMessage.Broadcast(Consumer.Get(), UEMessage);
			}
			else
			{
				delete ClonedMessage;
			}
		}
		else
		{
			delete ClonedMessage;
		}
	});
}
