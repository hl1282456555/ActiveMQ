// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActiveMQQueueBrowser.generated.h"

namespace cms
{
	class QueueBrowser;
}

class UActiveMQQueue;
class UActiveMQMessageEnumeration;

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQQueueBrowser : public UObject
{
	GENERATED_BODY()
public:
	virtual void SetInnerQueueBrowser(const TSharedPtr<cms::QueueBrowser>& NewQueueBrowser);
	FORCEINLINE virtual const TSharedPtr<cms::QueueBrowser>& GetInnerQueueBrowser() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | QueueBrowser")
	virtual void Close();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | QueueBrowser")
	virtual UActiveMQQueue* GetQueue() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | QueueBrowser")
	virtual FString GetMessageSelector() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | QueueBrowser")
	UActiveMQMessageEnumeration* GetMessageEnumeration();

private:
	TSharedPtr<cms::QueueBrowser> InnerQueueBrowser;
};
