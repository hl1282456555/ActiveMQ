// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveMQProperties.h"

#include "cms/CMSProperties.h"

UActiveMQProperties::UActiveMQProperties()
{
}

UActiveMQProperties::~UActiveMQProperties()
{
}

void UActiveMQProperties::SetInnerProperties(const TSharedPtr<cms::CMSProperties>& NewProperties)
{
	InnerProperties = NewProperties;
}

const TSharedPtr<cms::CMSProperties>& UActiveMQProperties::GetInnerProperties() const
{
	return InnerProperties;
}

int32 UActiveMQProperties::GetSize() const
{
	return InnerProperties ? InnerProperties->size() : 0;
}

bool UActiveMQProperties::IsEmpty() const
{
	return InnerProperties ? InnerProperties->isEmpty() : true;
}

FString UActiveMQProperties::GetProperty(const FString& PropertyName, const FString& DefaultValue) const
{
	if (!InnerProperties)
	{
		return DefaultValue;
	}

	std::string PropertyValue = InnerProperties->getProperty(TCHAR_TO_UTF8(*PropertyName), TCHAR_TO_UTF8(*DefaultValue));
	return FString(UTF8_TO_TCHAR(PropertyValue.c_str()));
}

void UActiveMQProperties::SetProperty(const FString& PropertyName, const FString& Value)
{
	if (InnerProperties)
	{
		InnerProperties->setProperty(TCHAR_TO_UTF8(*PropertyName), TCHAR_TO_UTF8(*Value));
	}
}

bool UActiveMQProperties::HasProperty(const FString& PropertyName) const
{
	return InnerProperties ? InnerProperties->hasProperty(TCHAR_TO_UTF8(*PropertyName)) : false;
}

FString UActiveMQProperties::RemoveProperty(const FString& PropertyName)
{
	if (InnerProperties)
	{
		std::string PropertyValue = InnerProperties->getProperty(TCHAR_TO_UTF8(*PropertyName));
		return FString(UTF8_TO_TCHAR(PropertyValue.c_str()));
	}

	return TEXT("");
}

TArray<FString> UActiveMQProperties::GetPropertyNames() const
{
	TArray<FString> Result;
	if (InnerProperties)
	{
		std::vector<std::string> PropertyNames = InnerProperties->propertyNames();
		for (const std::string& PropertyName : PropertyNames)
		{
			Result.Add(FString(UTF8_TO_TCHAR(PropertyName.c_str())));
		}
	}

	return Result;
}

TMap<FString, FString> UActiveMQProperties::ToMap() const
{
	TMap<FString, FString> Result;
	if (InnerProperties)
	{
		std::vector<std::pair<std::string, std::string>> SourceMap = InnerProperties->toArray();
		for (const std::pair<std::string, std::string>& Pair : SourceMap)
		{
			Result.Add(UTF8_TO_TCHAR(Pair.first.c_str()), UTF8_TO_TCHAR(Pair.second.c_str()));
		}
	}

	return Result;
}

void UActiveMQProperties::Copy(UActiveMQProperties* Source)
{
	if (InnerProperties && Source->InnerProperties)
	{
		InnerProperties->copy(Source->InnerProperties.Get());
	}
}

UActiveMQProperties* UActiveMQProperties::Clone() const
{
	UActiveMQProperties* NewProperties = NewObject<UActiveMQProperties>(GetOuter());
	NewProperties->SetInnerProperties(MakeShareable(InnerProperties->clone()));
	
	return NewProperties;
}

void UActiveMQProperties::Clear()
{
	if (InnerProperties)
	{
		InnerProperties->clear();
	}
}

FString UActiveMQProperties::ToString() const
{
	return InnerProperties ? UTF8_TO_TCHAR(InnerProperties->toString().c_str()) : TEXT("");
}
