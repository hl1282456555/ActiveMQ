// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveMQMessage.h"
#include "ActiveMQBytesMessage.generated.h"

/**
 * 
 */
UCLASS()
class ACTIVEMQ_API UActiveMQBytesMessage : public UActiveMQMessage
{
	GENERATED_BODY()
public:
	virtual EActiveMQMessageType GetMessageType() const override;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void SetBodyBytes(const TArray<uint8>& InBodyBytes);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual TArray<uint8> GetBodyBytes() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual int32 GetBodyLength() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void Reset();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual bool ReadBoolean() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void WriteBoolean(bool Value) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual uint8 ReadByte() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void WriteByte(uint8 Value) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual int32 ReadBytes(UPARAM(ref)TArray<uint8>& Bytes) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void WriteBytes(const TArray<uint8>& InBytes) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage", meta = (DisplayName = "ReadBytes (With Length)"))
	virtual int32 ReadBytes_WithLength(UPARAM(ref)TArray<uint8>& Buffer, int32 Length) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage", meta = (DisplayName = "WriteBytes (With Params)"))
	virtual void WriteBytes_WithParams(const TArray<uint8>& InBytes, int32 Offset, int32 Length) const;
	
	virtual char ReadChar() const;
	
	virtual void WriteChar(char Value) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual float ReadFloat() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void WriteFloat(float Value) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual double ReadDouble() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void WriteDouble(double Value) const;
	
	virtual short ReadShort() const;
	
	virtual void WriteShort(short Value) const;
	
	virtual unsigned short ReadUnsignedShort() const;
	
	virtual void WriteUnsignedShort(unsigned short Value) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual int32 ReadInt() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void WriteInt(int32 Value) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual int64 ReadLong() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void WriteLong(int64 Value) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual FString ReadString() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void WriteString(const FString& Value) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Message | BytesMessage")
	virtual FString ReadUTF() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Message | BytesMessage")
	virtual void WriteUTF(const FString& Value) const;
};
