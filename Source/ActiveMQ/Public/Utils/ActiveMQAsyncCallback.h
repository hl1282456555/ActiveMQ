// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

THIRD_PARTY_INCLUDES_START
#include "cms/AsyncCallback.h"
THIRD_PARTY_INCLUDES_END

class UActiveMQProducer;

class ACTIVEMQ_API FActiveMQProducerCallback : public cms::AsyncCallback
{
public:
	FActiveMQProducerCallback(const TWeakObjectPtr<UActiveMQProducer>& InProducer);
	virtual ~FActiveMQProducerCallback() override;

protected:
	virtual void onSuccess() override;
	virtual void onException(const cms::CMSException& Exception) override;

protected:
	TWeakObjectPtr<UActiveMQProducer> Producer;
};
