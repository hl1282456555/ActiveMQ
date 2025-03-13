// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#include "cms/MessageListener.h"
THIRD_PARTY_INCLUDES_END

namespace cms
{
	class Message;
}

class UActiveMQConsumer;

/**
 * 
 */
class ACTIVEMQ_API FActiveMQMessageListener : public cms::MessageListener
{
public:
	FActiveMQMessageListener(const TWeakObjectPtr<UActiveMQConsumer>& InConsumer);
	virtual ~FActiveMQMessageListener() override;

protected:
	virtual void onMessage(const cms::Message* Message) override;

protected:
	TWeakObjectPtr<UActiveMQConsumer> Consumer;
};
