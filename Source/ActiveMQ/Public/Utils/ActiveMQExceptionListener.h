// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveMQSubsystem.h"

THIRD_PARTY_INCLUDES_START
#include "cms/ExceptionListener.h"
THIRD_PARTY_INCLUDES_END

/**
 * 
 */
class ACTIVEMQ_API FActiveMQExceptionListener : public cms::ExceptionListener
{
public:
	FActiveMQExceptionListener(const TWeakObjectPtr<UObject>& InOwner, EActiveMQExceptionOwnerType InOwnerType);
	virtual ~FActiveMQExceptionListener() override;

protected:
	virtual void onException(const cms::CMSException& Exception) override;

protected:
	TWeakObjectPtr<UObject> OwnerObject;
	EActiveMQExceptionOwnerType OwnerType;
};
