// Fill out your copyright notice in the Description page of Project Settings.


#include "Messages/ActiveMQMessage.h"

#include "ActiveMQDestination.h"
#include "ActiveMQExceptionHelper.h"

THIRD_PARTY_INCLUDES_START
#include "cms/Message.h"
THIRD_PARTY_INCLUDES_END

void UActiveMQMessage::BeginDestroy()
{
	UObject::BeginDestroy();
}

void UActiveMQMessage::SetInnerMessage(const TSharedPtr<cms::Message>& NewMessage)
{
	InnerMessage = NewMessage;
}

const TSharedPtr<cms::Message>& UActiveMQMessage::GetInnerMessage() const
{
	return InnerMessage;
}

EActiveMQMessageType UActiveMQMessage::GetMessageType() const
{
	return EActiveMQMessageType::Unknown;
}

UActiveMQMessage* UActiveMQMessage::Clone() const
{
	UActiveMQMessage* NewMessage = NewObject<UActiveMQMessage>(GetOuter());
	NewMessage->InnerMessage = MakeShareable(InnerMessage->clone());

	return NewMessage;
}

void UActiveMQMessage::Acknowledge() const
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->acknowledge();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

void UActiveMQMessage::ClearBody()
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->clearBody();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

void UActiveMQMessage::ClearProperties()
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->clearProperties();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

TArray<FString> UActiveMQMessage::GetPropertyNames() const
{
	TArray<FString> Result;
	if (InnerMessage)
	{
		try
		{
			std::shared_ptr<std::vector<std::string>> PropertyNames = InnerMessage->getPropertyNames();
			for (const std::string& PropertyName : *PropertyNames)
			{
				Result.Add(UTF8_TO_TCHAR(PropertyName.c_str()));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return Result;
}

bool UActiveMQMessage::PropertyExists(const FString& PropertyName) const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->propertyExists(TCHAR_TO_UTF8(*PropertyName));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return false;
}

EActiveMQMessageValueType UActiveMQMessage::GetPropertyValueType(const FString& PropertyName) const
{
	if (InnerMessage)
	{
		try
		{
			return static_cast<EActiveMQMessageValueType>(InnerMessage->getPropertyValueType(TCHAR_TO_UTF8(*PropertyName)));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return EActiveMQMessageValueType::Unknown;
}

bool UActiveMQMessage::GetBooleanProperty(const FString& PropertyName) const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getBooleanProperty(TCHAR_TO_UTF8(*PropertyName));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return false;
}

uint8 UActiveMQMessage::GetByteProperty(const FString& PropertyName) const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getByteProperty(TCHAR_TO_UTF8(*PropertyName));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

double UActiveMQMessage::GetDoubleProperty(const FString& PropertyName) const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getDoubleProperty(TCHAR_TO_UTF8(*PropertyName));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0.0f;
}

float UActiveMQMessage::GetFloatProperty(const FString& PropertyName) const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getFloatProperty(TCHAR_TO_UTF8(*PropertyName));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0.0f;
}

int32 UActiveMQMessage::GetIntProperty(const FString& PropertyName) const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getIntProperty(TCHAR_TO_UTF8(*PropertyName));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

int64 UActiveMQMessage::GetLongProperty(const FString& PropertyName) const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getLongProperty(TCHAR_TO_UTF8(*PropertyName));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

short UActiveMQMessage::GetShortProperty(const FString& PropertyName) const
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->getShortProperty(TCHAR_TO_UTF8(*PropertyName));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

FString UActiveMQMessage::GetStringProperty(const FString& PropertyName) const
{
	if (InnerMessage)
	{
		try
		{
			return UTF8_TO_TCHAR(InnerMessage->getStringProperty(TCHAR_TO_UTF8(*PropertyName))->c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return TEXT("");
}

void UActiveMQMessage::SetBooleanProperty(const FString& PropertyName, bool PropertyValue)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setBooleanProperty(TCHAR_TO_UTF8(*PropertyName), PropertyValue);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

void UActiveMQMessage::SetByteProperty(const FString& PropertyName, uint8 PropertyValue)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setByteProperty(TCHAR_TO_UTF8(*PropertyName), PropertyValue);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

void UActiveMQMessage::SetDoubleProperty(const FString& PropertyName, double PropertyValue)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setDoubleProperty(TCHAR_TO_UTF8(*PropertyName), PropertyValue);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

void UActiveMQMessage::SetFloatProperty(const FString& PropertyName, float PropertyValue)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setFloatProperty(TCHAR_TO_UTF8(*PropertyName), PropertyValue);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

void UActiveMQMessage::SetIntProperty(const FString& PropertyName, int32 PropertyValue)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setIntProperty(TCHAR_TO_UTF8(*PropertyName), PropertyValue);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

void UActiveMQMessage::SetLongProperty(const FString& PropertyName, int64 PropertyValue)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setLongProperty(TCHAR_TO_UTF8(*PropertyName), PropertyValue);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

void UActiveMQMessage::SetShortProperty(const FString& PropertyName, short PropertyValue)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setShortProperty(TCHAR_TO_UTF8(*PropertyName), PropertyValue);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

void UActiveMQMessage::SetStringProperty(const FString& PropertyName, const FString& PropertyValue)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setStringProperty(TCHAR_TO_UTF8(*PropertyName), TCHAR_TO_UTF8(*PropertyValue));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

FString UActiveMQMessage::GetCMSCorrelationID() const
{
	if (InnerMessage)
	{
		try
		{
			return UTF8_TO_TCHAR(InnerMessage->getCMSCorrelationID()->c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return TEXT("");
}

void UActiveMQMessage::SetCMSCorrelationID(const FString& CorrelationId)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setCMSCorrelationID(TCHAR_TO_UTF8(*CorrelationId));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int32 UActiveMQMessage::GetCMSDeliveryMode() const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getCMSDeliveryMode();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQMessage::SetCMSDeliveryMode(int32 DeliveryMode)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setCMSDeliveryMode(DeliveryMode);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

UActiveMQDestination* UActiveMQMessage::GetCMSDestination() const
{
	UActiveMQDestination* NewDestination = NewObject<UActiveMQDestination>(GetOuter());
	NewDestination->SetInnerDestination(MakeShareable(InnerMessage->getCMSDestination()->clone()));

	return NewDestination;
}

void UActiveMQMessage::SetCMSDestination(UActiveMQDestination* Destination)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setCMSDestination(Destination->GetInnerDestination().Get());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int64 UActiveMQMessage::GetCMSExpiration() const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getCMSExpiration();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQMessage::SetCMSExpiration(int64 ExpireTime)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setCMSExpiration(ExpireTime);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

FString UActiveMQMessage::GetCMSMessageID() const
{
	if (InnerMessage)
	{
		try
		{
			return UTF8_TO_TCHAR(InnerMessage->getCMSMessageID()->c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return TEXT("");
}

void UActiveMQMessage::SetCMSMessageID(const FString& MessageID)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setCMSMessageID(TCHAR_TO_UTF8(*MessageID));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int32 UActiveMQMessage::GetCMSPriority() const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getCMSPriority();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQMessage::SetCMSPriority(int32 Priority)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setCMSPriority(Priority);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

bool UActiveMQMessage::GetCMSRedelivered() const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getCMSRedelivered();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return false;
}

void UActiveMQMessage::SetCMSRedelivered(bool Redelivered)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setCMSRedelivered(Redelivered);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

UActiveMQDestination* UActiveMQMessage::GetCMSReplyTo() const
{
	if (InnerMessage)
	{
		try
		{
			UActiveMQDestination* NewDestination = NewObject<UActiveMQDestination>(GetOuter());
			NewDestination->SetInnerDestination(MakeShareable(InnerMessage->getCMSReplyTo()->clone()));
			return NewDestination;
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return nullptr;
}

void UActiveMQMessage::SetCMSReplyTo(UActiveMQDestination* Destination)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setCMSReplyTo(Destination->GetInnerDestination().Get());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int64 UActiveMQMessage::GetCMSTimestamp() const
{
	if (InnerMessage)
	{
		try
		{
			return InnerMessage->getCMSTimestamp();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQMessage::SetCMSTimestamp(int64 Timestamp)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setCMSTimestamp(Timestamp);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

FString UActiveMQMessage::GetCMSType() const
{
	if (InnerMessage)
	{
		try
		{
			return UTF8_TO_TCHAR(InnerMessage->getCMSType()->c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return TEXT("");
}

void UActiveMQMessage::SetCMSType(const FString& MessageType)
{
	if (InnerMessage)
	{
		try
		{
			InnerMessage->setCMSType(TCHAR_TO_UTF8(*MessageType));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}
