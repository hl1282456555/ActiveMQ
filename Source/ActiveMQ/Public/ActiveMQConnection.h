// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActiveMQSession.h"
#include "ActiveMQConnection.generated.h"

USTRUCT(BlueprintType)
struct ACTIVEMQ_API FActiveMQConnectionMetaData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQ | Connection | MetaData")
	FString CMSVersion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQ | Connection | MetaData")
	int32 CMSMajorVersion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQ | Connection | MetaData")
	int32 CMSMinorVersion;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQ | Connection | MetaData")
	FString CMSProviderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQ | Connection | MetaData")
	FString ProviderVersion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQ | Connection | MetaData")
	int32 ProviderMajorVersion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQ | Connection | MetaData")
	int32 ProviderMinorVersion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQ | Connection | MetaData")
	int32 ProviderPatchVersion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActiveMQ | Connection | MetaData")
	TArray<FString> CMSXPropertyNames;

	FActiveMQConnectionMetaData();
};

namespace cms
{
	class Connection;
}

class FActiveMQExceptionListener;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveMQConnectionClosedDelegate, UActiveMQConnection*, Connection);

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQConnection : public UObject
{
	GENERATED_BODY()
public:
	virtual void BeginDestroy() override;

	virtual void SetInnerConnection(const TSharedPtr<cms::Connection>& NewConnection);
	virtual const TSharedPtr<cms::Connection>& GetInnerConnection() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Connection")
	FActiveMQConnectionMetaData GetMetaData() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Connection")
	void Start();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Connection")
	void Close();

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Connection")
	void Stop();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Connection")
	UActiveMQSession* CreateSession(EActiveMQSessionAcknowledgeMode AcknowledgeMode = EActiveMQSessionAcknowledgeMode::AUTO_ACKNOWLEDGE);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Connection")
	FString GetClientID() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Connection")
	void SetClientID(const FString& InClientID);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Connection")
	TArray<UActiveMQSession*> GetAllSessions() const;

protected:
	UFUNCTION()
	void HandleSessionCloseEvent(UActiveMQSession* Session);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "ActiveMQ | Connection")
	FOnActiveMQConnectionClosedDelegate OnClosed;

protected:
	UPROPERTY()
	TArray<UActiveMQSession*> Sessions;

	TSharedPtr<FActiveMQExceptionListener> ExceptionListener;
	
private:
	TSharedPtr<cms::Connection> InnerConnection;
};
