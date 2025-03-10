// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActiveMQExceptionHelper.h"
#include "ActiveMQSession.generated.h"

UENUM(BlueprintType)
enum class EActiveMQSessionAcknowledgeMode : uint8
{
	/**
 	* With this acknowledgment mode, the session automatically
 	* acknowledges a client's receipt of a message either when
 	* the session has successfully returned from a call to receive
 	* or when the message listener the session has called to
 	* process the message successfully returns.
 	*/
	AUTO_ACKNOWLEDGE = 0,

	/**
	 * With this acknowledgment mode, the session automatically
	 * acknowledges a client's receipt of a message either when
	 * the session has successfully returned from a call to receive
	 * or when the message listener the session has called to
	 * process the message successfully returns.  Acknowledgments
	 * may be delayed in this mode to increase performance at
	 * the cost of the message being redelivered this client fails.
	 */
	DUPS_OK_ACKNOWLEDGE,

	/**
	 * With this acknowledgment mode, the client acknowledges a
	 * consumed message by calling the message's acknowledge method.
	 */
	CLIENT_ACKNOWLEDGE,

	/**
	 * Messages will be consumed when the transaction commits.
	 */
	SESSION_TRANSACTED,

	/**
	 * Message will be acknowledged individually.  Normally the acks sent
	 * acknowledge the given message and all messages received before it, this
	 * mode only acknowledges one message.
	 */
	INDIVIDUAL_ACKNOWLEDGE
};

namespace cms
{
	class Session;
}

class UActiveMQDestination;
class UActiveMQQueue;
class UActiveMQTopic;
class UActiveMQTemporaryQueue;
class UActiveMQTemporaryTopic;
class UActiveMQConsumer;
class UActiveMQProducer;
class UActiveMQQueueBrowser;

class UActiveMQBytesMessage;
class UActiveMQStreamMessage;
class UActiveMQTextMessage;
class UActiveMQMapMessage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActiveMQSessionCloseDelegate);

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQSession : public UObject
{
	GENERATED_BODY()
public:
	UActiveMQSession();
	virtual ~UActiveMQSession() override;

	virtual void BeginDestroy() override;

	virtual void SetInnerSession(const TSharedPtr<cms::Session>& InSession);
	FORCEINLINE virtual const TSharedPtr<cms::Session>& GetInnerSession() const;
	
	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	FString GetSessionID() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Session")
	void SetSessionID(const FString& InSessionID);
	
	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Session")
	void Start();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Session")
	void Close();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Session")
	void Stop();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Session")
	void Commit();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Session")
	void Rollback();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Session")
	void Recover();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQConsumer* CreateConsumer(UActiveMQDestination* Destination, const FString& Selector, bool bNoLocal = false);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQConsumer* CreateDurableConsumer(UActiveMQTopic* Topic, const FString& Name, const FString& Selector, bool bNoLocal = false);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQProducer* CreateProducer(UActiveMQDestination* Destination = nullptr);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQQueueBrowser* CreateBrowser(UActiveMQQueue* Queue, const FString& Selector);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQQueue* CreateQueue(const FString& QueueName);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQTopic* CreateTopic(const FString& TopicName);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQTemporaryQueue* CreateTemporaryQueue();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQTemporaryTopic* CreateTemporaryTopic();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQMessage* CreateMessage();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQBytesMessage* CreateBytesMessage(const TArray<uint8>& Bytes);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQStreamMessage* CreateStreamMessage();

	UFUNCTION(Blueprintpure, Category = "ActiveMQ | Session")
	UActiveMQTextMessage* CreateTextMessage(const FString& Text);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	UActiveMQMapMessage* CreateMapMessage();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	EActiveMQSessionAcknowledgeMode GetAcknowledgeMode() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Session")
	bool IsTransacted() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Session")
	void Unsubscribe(const FString& Name);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetSessionID", Getter, BlueprintGetter="GetSessionID", Category = "ActiveMQ | Session")
	FString SessionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQ | Session")
	FOnActiveMQSessionCloseDelegate OnSessionClose;
	
private:
	TSharedPtr<cms::Session> InnerSession;
};
