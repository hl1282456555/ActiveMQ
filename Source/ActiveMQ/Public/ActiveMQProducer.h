// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
THIRD_PARTY_INCLUDES_START
#include "cms/AsyncCallback.h"
THIRD_PARTY_INCLUDES_END
#include "ActiveMQProducer.generated.h"

namespace cms
{
	class MessageProducer;
}

class UActiveMQMessage;
class UActiveMQDestination;

UENUM(BlueprintType)
enum class EActiveMQDeliveryMode : uint8
{
	Persistent = 0,
	Non_Persistent
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveMQProducerSendAsyncCompleteDelegate, UActiveMQProducer*, Producer, bool, bSuccess);

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQProducer : public UObject, public cms::AsyncCallback
{
	GENERATED_BODY()
public:
	virtual void BeginDestroy() override;

	virtual void SetInnerProducer(const TSharedPtr<cms::MessageProducer>& NewProducer);
	FORCEINLINE virtual const TSharedPtr<cms::MessageProducer>& GetInnerProducer() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer")
	virtual void Close();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer")
	virtual void Send(UActiveMQMessage* Message);
	
	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer", meta = (DisplayName = "Send (With Params)"))
	virtual void Send_WithParams(UActiveMQMessage* Message, EActiveMQDeliveryMode DeliveryMode, int32 Priority, int64 TimeToLive);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer")
	virtual void AsyncSend(UActiveMQMessage* Message);
	
	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer", meta = (DisplayName = "AsyncSend (With Params)"))
	virtual void AsyncSend_WithParams(UActiveMQMessage* Message, EActiveMQDeliveryMode DeliveryMode, int32 Priority, int64 TimeToLive);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer")
	virtual void SendTo(UActiveMQDestination* Destination, UActiveMQMessage* Message);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer", meta = (DisplayName = "SendTo (With Params)"))
	virtual void SendTo_WithParams(UActiveMQDestination* Destination, UActiveMQMessage* Message, EActiveMQDeliveryMode DeliveryMode, int32 Priority, int64 TimeToLive);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer")
	virtual void AsyncSendTo(UActiveMQDestination* Destination, UActiveMQMessage* Message);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer", meta = (DisplayName = "AsyncSendTo (With Params)"))
	virtual void AsyncSendTo_WithParams(UActiveMQDestination* Destination, UActiveMQMessage* Message, EActiveMQDeliveryMode DeliveryMode, int32 Priority, int64 TimeToLive);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer")
	virtual void SetDeliveryMode(EActiveMQDeliveryMode Mode);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Producer")
	virtual EActiveMQDeliveryMode GetDeliveryMode() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer")
	virtual void SetDisableMessageID(bool bDisable);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Producer")
	virtual bool GetDisableMessageID() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer")
	virtual void SetDisableMessageTimeStamp(bool bDisable);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Producer")
	virtual bool GetDisableMessageTimeStamp() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer")
	virtual void SetPriority(int32 Priority);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Producer")
	virtual int32 GetPriority() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Producer")
	virtual void SetTimeToLive(int64 Time);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Producer")
	virtual int64 GetTimeToLive() const;

protected:
	virtual void onSuccess() override;
	virtual void onException(const cms::CMSException& Exception) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "ActiveMQ | Producer")
	FOnActiveMQProducerSendAsyncCompleteDelegate OnSendAsyncComplete;
	
private:
	TSharedPtr<cms::MessageProducer> InnerProducer;
};
