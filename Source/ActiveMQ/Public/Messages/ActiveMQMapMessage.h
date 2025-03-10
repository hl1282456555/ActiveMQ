// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveMQMessage.h"
#include "ActiveMQMapMessage.generated.h"

/**
 * 
 */
UCLASS()
class ACTIVEMQ_API UActiveMQMapMessage : public UActiveMQMessage
{
	GENERATED_BODY()
public:
	virtual EActiveMQMessageType GetMessageType() const override;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual bool IsEmpty() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual TArray<FString> GetMapNames() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual bool ItemExists(const FString& Name) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual EActiveMQMessageValueType GetValueType(const FString& Name) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual bool GetBoolean(const FString& Name) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | MapMessage")
	virtual void SetBoolean(const FString& Name, bool Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual uint8 GetByte(const FString& Name) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | MapMessage")
	virtual void SetByte(const FString& Name, uint8 Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual TArray<uint8> GetBytes(const FString& Name) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | MapMessage")
	virtual void SetBytes(const FString& Name, const TArray<uint8>& Value);
	
	virtual char GetChar(const FString& Name) const;
	
	virtual void SetChar(const FString& Name, char Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual double GetDouble(const FString& Name) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | MapMessage")
	virtual void SetDouble(const FString& Name, double Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual float GetFloat(const FString& Name) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | MapMessage")
	virtual void SetFloat(const FString& Name, float Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual int32 GetInt(const FString& Name) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | MapMessage")
	virtual void SetInt(const FString& Name, int32 Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual int64 GetLong(const FString& Name) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | MapMessage")
	virtual void SetLong(const FString& Name, int64 Value);
	
	virtual short GetShort(const FString& Name) const;
	
	virtual void SetShort(const FString& Name, short Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | MapMessage")
	virtual FString GetString(const FString& Name) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | MapMessage")
	virtual void SetString(const FString& Name, const FString& Value);
};
