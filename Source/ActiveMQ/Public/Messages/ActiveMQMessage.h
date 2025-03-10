// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActiveMQMessage.generated.h"

UENUM(BlueprintType)
enum class EActiveMQMessageValueType : uint8
{
	Null = 0,
	Boolean,
	Byte,
	Char,
	Short,
	Integer,
	Long,
	Double,
	Float,
	String,
	ByteArray,
	Unknown
};

UENUM(BlueprintType)
enum class EActiveMQMessageType : uint8
{
	Unknown = 0,
	TextMessage,
	ObjectMessage,
	StreamMessage,
	MapMessage,
	BytesMessage
};

namespace cms
{
	class Message;
}

class UActiveMQDestination;

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQMessage : public UObject
{
	GENERATED_BODY()
public:
	virtual void BeginDestroy() override;

	virtual void SetInnerMessage(const TSharedPtr<cms::Message>& NewMessage);
	virtual const TSharedPtr<cms::Message>& GetInnerMessage() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual EActiveMQMessageType GetMessageType() const;
	
	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual UActiveMQMessage* Clone() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void Acknowledge() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void ClearBody();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void ClearProperties();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual TArray<FString> GetPropertyNames() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual bool PropertyExists(const FString& PropertyName) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual EActiveMQMessageValueType GetPropertyValueType(const FString& PropertyName) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual bool GetBooleanProperty(const FString& PropertyName) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual uint8 GetByteProperty(const FString& PropertyName) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual double GetDoubleProperty(const FString& PropertyName) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual float GetFloatProperty(const FString& PropertyName) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual int32 GetIntProperty(const FString& PropertyName) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual int64 GetLongProperty(const FString& PropertyName) const;
	
	virtual short GetShortProperty(const FString& PropertyName) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual FString GetStringProperty(const FString& PropertyName) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetBooleanProperty(const FString& PropertyName, bool PropertyValue);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetByteProperty(const FString& PropertyName, uint8 PropertyValue);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetDoubleProperty(const FString& PropertyName, double PropertyValue);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetFloatProperty(const FString& PropertyName, float PropertyValue);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetIntProperty(const FString& PropertyName, int32 PropertyValue);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetLongProperty(const FString& PropertyName, int64 PropertyValue);
	
	virtual void SetShortProperty(const FString& PropertyName, short PropertyValue);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetStringProperty(const FString& PropertyName, const FString& PropertyValue);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual FString GetCMSCorrelationID() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetCMSCorrelationID(const FString& CorrelationId);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual int32 GetCMSDeliveryMode() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetCMSDeliveryMode(int32 DeliveryMode);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual UActiveMQDestination* GetCMSDestination() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetCMSDestination(UActiveMQDestination* Destination);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual int64 GetCMSExpiration() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetCMSExpiration(int64 ExpireTime);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual FString GetCMSMessageID() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetCMSMessageID(const FString& MessageID);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual int32 GetCMSPriority() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetCMSPriority(int32 Priority);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual bool GetCMSRedelivered() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetCMSRedelivered(bool Redelivered);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual UActiveMQDestination* GetCMSReplyTo() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetCMSReplyTo(UActiveMQDestination* Destination);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	virtual int64 GetCMSTimestamp() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetCMSTimestamp(int64 Timestamp);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message")
	FString GetCMSType() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message")
	virtual void SetCMSType(const FString& MessageType);
	
protected:
	TSharedPtr<cms::Message> InnerMessage;
};
