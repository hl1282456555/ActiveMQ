// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActiveMQProperties.generated.h"

namespace cms
{
	class CMSProperties;
}

/**
 * 
 */
UCLASS(BlueprintType)
class ACTIVEMQ_API UActiveMQProperties : public UObject
{
	GENERATED_BODY()
public:
	UActiveMQProperties();
	virtual ~UActiveMQProperties() override;

	virtual void SetInnerProperties(const TSharedPtr<cms::CMSProperties>& NewProperties);
	FORCEINLINE virtual const TSharedPtr<cms::CMSProperties>& GetInnerProperties() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Properties")
	int32 GetSize() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Properties")
	bool IsEmpty() const;
	
	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Properties")
	FString GetProperty(const FString& PropertyName, const FString& DefaultValue = TEXT("")) const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Properties")
	void SetProperty(const FString& PropertyName, const FString& Value);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Properties")
	bool HasProperty(const FString& PropertyName) const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Properties")
	FString RemoveProperty(const FString& PropertyName);

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Properties")
	TArray<FString> GetPropertyNames() const;

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Properties")
	TMap<FString, FString> ToMap() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Properties")
	void Copy(UActiveMQProperties* Source);
	
	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Properties")
	UActiveMQProperties* Clone() const;

	UFUNCTION(BlueprintCallable, Category = "ActiveMQ | Properties")
	void Clear();

	UFUNCTION(BlueprintPure, Category = "ActiveMQ | Properties")
	FString ToString() const;

private:
	TSharedPtr<cms::CMSProperties> InnerProperties;
};
