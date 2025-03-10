// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ActiveMQSubsystem.generated.h"

namespace cms
{
	class Message;
}

class UActiveMQConnection;
class UActiveMQSession;
class UActiveMQDestination;
class UActiveMQConsumer;
class UActiveMQMessage;

UENUM(BlueprintType)
enum class EActiveMQExceptionOwnerType : uint8
{
	EOT_Subsystem = 0,
	EOT_Connection,
	EOT_Session,
	EOT_Destination,
	EOT_Consumer,
	EOT_Producer,
	EOT_Message,
	EOT_MessageEnumeration,
	EOT_QueueBrowser
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActiveMQThrowExceptionDelegate, const FString, Owner, EActiveMQExceptionOwnerType, OwnerType, const FString&, Message);

/**
 * 
 */
UCLASS()
class ACTIVEMQ_API UActiveMQSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UActiveMQMessage* ConvertCMSMessageToUEMessage(UObject* Outer, cms::Message* InMessage);

	UFUNCTION(BlueprintPure, Category = "ActiveMQSubsystem")
	virtual UActiveMQConnection* CreateConnection(const FString& BrokerURI, const FString& Username, const FString& Password, const FString& ClientId = TEXT(""));
	
	UFUNCTION(BlueprintCallable, Category = "ActiveMQSubsystem")
	virtual void DispatchExceptionMessage(const FString Owner, EActiveMQExceptionOwnerType OwnerType, const FString& Message);
	
protected:
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQSubsystem")
	FOnActiveMQThrowExceptionDelegate OnActiveMQThrowException;
};
