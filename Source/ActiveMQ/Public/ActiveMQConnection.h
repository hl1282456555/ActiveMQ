// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
THIRD_PARTY_INCLUDES_START
#include "cms/ExceptionListener.h"
THIRD_PARTY_INCLUDES_END
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveMQConnectionCloseDelegate, UActiveMQConnection*, Connection);

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQConnection : public UObject, public cms::ExceptionListener
{
	GENERATED_BODY()
public:
	UActiveMQConnection();
	virtual ~UActiveMQConnection() override;

	virtual void BeginDestroy() override;

	virtual void SetInnerConnection(const TSharedPtr<cms::Connection>& NewConnection);
	FORCEINLINE virtual const TSharedPtr<cms::Connection>& GetInnerConnection() const;
	
	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Connection")
	FString GetUsername() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Connection")
	void SetUsername(const FString& InUsername);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Connection")
	FString GetPassword() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Connection")
	void SetPassword(const FString& InPassword);

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

protected:
	virtual void onException(const cms::CMSException& Exception) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetUsername", Getter, BlueprintGetter="GetUsername", Category = "ActiveMQ | Connection")
	FString Username;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Setter, BlueprintSetter="SetPassword", Getter, BlueprintGetter="GetPassword", Category = "ActiveMQ | Connection")
	FString Password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "ActiveMQ | Connection")
	FOnActiveMQConnectionCloseDelegate OnConnectionClosed;
	
private:
	TSharedPtr<cms::Connection> InnerConnection;
};
