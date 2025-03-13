// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActiveMQDestination.generated.h"

class UActiveMQProperties;

namespace cms
{
	class Destination;
}

UENUM(BlueprintType)
enum class EActiveMQDestinationType : uint8
{
	Topic = 0,
	Queue,
	Temporary_Topic,
	Temporary_Queue,
};

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQDestination : public UObject
{
	GENERATED_BODY()
public:
	virtual void BeginDestroy() override;

	virtual void SetInnerDestination(const TSharedPtr<cms::Destination>& NewDestination);
	virtual const TSharedPtr<cms::Destination>& GetInnerDestination() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Destination")
	virtual EActiveMQDestinationType GetDestinationType() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Destination")
	virtual UActiveMQDestination* Clone() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Destination")
	virtual void Copy(UActiveMQDestination* Source);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Destination")
	virtual bool Equals(UActiveMQDestination* Other) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Destination")
	UActiveMQProperties* GetProperties() const;

protected:
	TSharedPtr<cms::Destination> InnerDestination;
};

UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQTopic : public UActiveMQDestination
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Destination | Topic")
	FString GetTopicName() const;
};

UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQQueue : public UActiveMQDestination
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Destination | Queue")
	FString GetQueueName() const;
};

UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQTemporaryQueue : public UActiveMQQueue
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Destination | Temporary Queue")
	virtual void Destroy();
};

UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQTemporaryTopic : public UActiveMQTopic
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Destination | Temporary Topic")
	virtual void Destroy();
};