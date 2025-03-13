// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/ActiveMQExceptionListener.h"

#include "ActiveMQExceptionHelper.h"

FActiveMQExceptionListener::FActiveMQExceptionListener(const TWeakObjectPtr<UObject>& InOwner, EActiveMQExceptionOwnerType InOwnerType)
	: OwnerObject(InOwner)
	, OwnerType(InOwnerType)
{
}

FActiveMQExceptionListener::~FActiveMQExceptionListener()
{
	OwnerObject.Reset();
}

void FActiveMQExceptionListener::onException(const cms::CMSException& Exception)
{
	AsyncTask(ENamedThreads::Type::GameThread, [Exception, this]()
	{
		DeliverException(OwnerObject.Get(), OwnerObject->GetName(), OwnerType, Exception);
	});
}
