// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActiveMQMessageEnumeration.generated.h"

namespace cms
{
	class MessageEnumeration;
}

class UActiveMQMessage;

/**
 * 
 */
UCLASS()
class ACTIVEMQ_API UActiveMQMessageEnumeration : public UObject
{
	GENERATED_BODY()
public:
	virtual void SetInnerEnumeration(const TSharedPtr<cms::MessageEnumeration>& NewEnumeration);
	virtual const TSharedPtr<cms::MessageEnumeration>& GetInnerEnumeration() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | Enumeration")
	virtual bool HasMoreMessages();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | Enumeration")
	virtual UActiveMQMessage* NextMessage();

private:
	TSharedPtr<cms::MessageEnumeration> InnerEnumeration;
};
