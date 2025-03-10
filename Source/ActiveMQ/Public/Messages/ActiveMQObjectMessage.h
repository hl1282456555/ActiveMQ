// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveMQMessage.h"
#include "ActiveMQObjectMessage.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQObjectMessage : public UActiveMQMessage
{
	GENERATED_BODY()
public:
	virtual EActiveMQMessageType GetMessageType() const override;
	
	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | ObjectMessage")
	virtual TArray<uint8> GetObjectBytes() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | ObjectMessage")
	virtual void SetObjectBytes(const TArray<uint8>& InBytes);
};
