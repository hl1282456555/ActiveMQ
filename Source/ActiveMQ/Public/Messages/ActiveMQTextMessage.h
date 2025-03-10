// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveMQMessage.h"
#include "ActiveMQTextMessage.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQTextMessage : public UActiveMQMessage
{
	GENERATED_BODY()
public:
	virtual EActiveMQMessageType GetMessageType() const override;
	
	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | TextMessage")
	virtual FString GetText() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | TextMessage")
	virtual void SetText(const FString& InMessage);
};
