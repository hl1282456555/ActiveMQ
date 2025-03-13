// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/ActiveMQAsyncCallback.h"

#include "ActiveMQExceptionHelper.h"
#include "ActiveMQProducer.h"
#include "ActiveMQSubsystem.h"

FActiveMQProducerCallback::FActiveMQProducerCallback(const TWeakObjectPtr<UActiveMQProducer>& InProducer)
	: Producer(InProducer)
{
}

FActiveMQProducerCallback::~FActiveMQProducerCallback()
{
	Producer.Reset();
}

void FActiveMQProducerCallback::onSuccess()
{
	AsyncTask(ENamedThreads::Type::GameThread, [&]()
	{
		if (Producer.IsValid())
		{
			Producer->OnSendAsyncComplete.Broadcast(Producer.Get(), true);
		}
	});
}

void FActiveMQProducerCallback::onException(const cms::CMSException& Exception)
{
	AsyncTask(ENamedThreads::Type::GameThread, [&, Exception]()
	{
		if (Producer.IsValid())
		{
			Producer->OnSendAsyncComplete.Broadcast(Producer.Get(), false);
			DeliverException(Producer.Get(), Producer->GetName(), EActiveMQExceptionOwnerType::EOT_Producer, Exception);
		}
	});
}
