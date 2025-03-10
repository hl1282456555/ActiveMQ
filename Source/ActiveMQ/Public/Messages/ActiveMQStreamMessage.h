// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveMQMessage.h"
#include "ActiveMQStreamMessage.generated.h"

/**
 * 
 */
UCLASS()
class ACTIVEMQ_API UActiveMQStreamMessage : public UActiveMQMessage
{
	GENERATED_BODY()
public:
	virtual EActiveMQMessageType GetMessageType() const override;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | StreamMessage")
	EActiveMQMessageValueType GetNextValueType() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | StreamMessage")
	virtual bool readBoolean() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | StreamMessage")
	virtual void writeBoolean(bool Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | StreamMessage")
	virtual uint8 ReadByte() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | StreamMessage")
	virtual void WriteByte(uint8 Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | StreamMessage")
	virtual int32 ReadBytes(UPARAM(ref)TArray<uint8>& Bytes) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | StreamMessage")
	virtual void WriteBytes(const TArray<uint8>& Bytes);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | StreamMessage", meta = (DisplayName = "ReadBytes (With Length)"))
	virtual int32 ReadBytes_WithLength(UPARAM(ref)TArray<uint8>& Buffer, int32 Length) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | StreamMessage", meta = (DisplayName = "WriteBytes (With Params)"))
	virtual void WriteBytes_WithParams(const TArray<uint8>& Buffer, int32 Offset, int32 Length);
	
	virtual char ReadChar() const;
	
	virtual void WriteChar(char Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | StreamMessage")
	virtual float ReadFloat() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | StreamMessage")
	virtual void WriteFloat(float Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | StreamMessage")
	virtual double ReadDouble() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | StreamMessage")
	virtual void WriteDouble(double Value);
	
	virtual short ReadShort() const;
	
	virtual void WriteShort(short Value);
	
	virtual unsigned short ReadUnsignedShort() const;
	
	virtual void WriteUnsignedShort(unsigned short Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | StreamMessage")
	virtual int32 ReadInt() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | StreamMessage")
	virtual void WriteInt(int32 Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | StreamMessage")
	virtual int64 ReadLong() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | StreamMessage")
	virtual void WriteLong(int64 Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | StreamMessage")
	virtual FString ReadString() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | StreamMessage")
	virtual void WriteString(const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | StreamMessage")
	virtual void Reset();
};
