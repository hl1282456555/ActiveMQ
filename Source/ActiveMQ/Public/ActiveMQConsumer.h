// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
THIRD_PARTY_INCLUDES_START
#include "cms/MessageListener.h"
THIRD_PARTY_INCLUDES_END
#include "ActiveMQConsumer.generated.h"

namespace cms
{
	class MessageConsumer;
}

class UActiveMQMessage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveMQConsumerReceivedMessageDeleagte, UActiveMQConsumer*, Consumer, UActiveMQMessage*, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveMQConsumerClosedDelegate, UActiveMQConsumer*, Consumer);

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQConsumer : public UObject, public cms::MessageListener
{
	GENERATED_BODY()
public:
	virtual void BeginDestroy() override;

	virtual void SetInnerConsumer(const TSharedPtr<cms::MessageConsumer>& NewConsumer);
	FORCEINLINE virtual const TSharedPtr<cms::MessageConsumer>& GetInnerConsumer() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Consumer")
	UActiveMQMessage* Receive();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Consumer", meta = (DisplayName = "Receive (TimeOut)"))
	UActiveMQMessage* Receive_WithTimeOut(int32 Millisecs);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Consumer")
	UActiveMQMessage* ReceiveNoWait();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Consumer")
	FString GetMessageSelector() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Consumer")
	void Start();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Consumer")
	void Close();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Consumer")
	void Stop();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "ActiveMQ | Consumer")
	FOnActiveMQConsumerReceivedMessageDeleagte OnReceivedMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "ActiveMQ | Consumer")
	FOnActiveMQConsumerClosedDelegate OnClosed;
	
protected:
	virtual void onMessage(const cms::Message* InMessage) override;

private:
	TSharedPtr<cms::MessageConsumer> InnerConsumer;
};
