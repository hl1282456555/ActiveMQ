// Fill out your copyright notice in the Description page of Project Settings.


#include "Messages/ActiveMQMapMessage.h"

THIRD_PARTY_INCLUDES_START
#include "cms/MapMessage.h"
THIRD_PARTY_INCLUDES_END

#include "ActiveMQExceptionHelper.h"

EActiveMQMessageType UActiveMQMapMessage::GetMessageType() const
{
	return EActiveMQMessageType::MapMessage;
}

bool UActiveMQMapMessage::IsEmpty() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->isEmpty();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return false;
}

TArray<FString> UActiveMQMapMessage::GetMapNames() const
{
	TArray<FString> Result;
	if (InnerMessage)
	{
		try
		{
			std::shared_ptr<std::vector<std::string>> Names = StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getMapNames();
			for (const std::string& Name : *Names)
			{
				Result.Add(UTF8_TO_TCHAR(Name.c_str()));
			}
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return Result;
}

bool UActiveMQMapMessage::ItemExists(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->itemExists(TCHAR_TO_UTF8(*Name));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return false;
}

EActiveMQMessageValueType UActiveMQMapMessage::GetValueType(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			return static_cast<EActiveMQMessageValueType>(StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getValueType(TCHAR_TO_UTF8(*Name)));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return EActiveMQMessageValueType::Unknown;
}

bool UActiveMQMapMessage::GetBoolean(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getBoolean(TCHAR_TO_UTF8(*Name));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return false;
}

void UActiveMQMapMessage::SetBoolean(const FString& Name, bool Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->setBoolean(TCHAR_TO_UTF8(*Name), Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

uint8 UActiveMQMapMessage::GetByte(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getByte(TCHAR_TO_UTF8(*Name));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQMapMessage::SetByte(const FString& Name, uint8 Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->setByte(TCHAR_TO_UTF8(*Name), Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

TArray<uint8> UActiveMQMapMessage::GetBytes(const FString& Name) const
{
	TArray<uint8> Result;
	if (InnerMessage)
	{
		try
		{
			std::shared_ptr<std::vector<uint8>> Bytes = StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getBytes(TCHAR_TO_UTF8(*Name));
			Result.SetNumUninitialized(Bytes->size());
			FMemory::Memcpy(Result.GetData(), Bytes->data(), Bytes->size());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return Result;
}

void UActiveMQMapMessage::SetBytes(const FString& Name, const TArray<uint8>& Value)
{
	if (InnerMessage)
	{
		try
		{
			std::vector<uint8> Bytes(Value.GetData(), Value.GetData() + Value.Num());
			StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->setBytes(TCHAR_TO_UTF8(*Name), Bytes);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

char UActiveMQMapMessage::GetChar(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getChar(TCHAR_TO_UTF8(*Name));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQMapMessage::SetChar(const FString& Name, char Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->setChar(TCHAR_TO_UTF8(*Name), Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

double UActiveMQMapMessage::GetDouble(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getDouble(TCHAR_TO_UTF8(*Name));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0.0f;
}

void UActiveMQMapMessage::SetDouble(const FString& Name, double Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->setDouble(TCHAR_TO_UTF8(*Name), Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

float UActiveMQMapMessage::GetFloat(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getFloat(TCHAR_TO_UTF8(*Name));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0.0f;
}

void UActiveMQMapMessage::SetFloat(const FString& Name, float Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->setFloat(TCHAR_TO_UTF8(*Name), Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int32 UActiveMQMapMessage::GetInt(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getInt(TCHAR_TO_UTF8(*Name));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQMapMessage::SetInt(const FString& Name, int32 Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->setInt(TCHAR_TO_UTF8(*Name), Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int64 UActiveMQMapMessage::GetLong(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getLong(TCHAR_TO_UTF8(*Name));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQMapMessage::SetLong(const FString& Name, int64 Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->setLong(TCHAR_TO_UTF8(*Name), Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

short UActiveMQMapMessage::GetShort(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getFloat(TCHAR_TO_UTF8(*Name));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQMapMessage::SetShort(const FString& Name, short Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->setShort(TCHAR_TO_UTF8(*Name), Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

FString UActiveMQMapMessage::GetString(const FString& Name) const
{
	if (InnerMessage)
	{
		try
		{
			std::shared_ptr<std::string> Value = StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->getString(TCHAR_TO_UTF8(*Name));
			return UTF8_TO_TCHAR(Value->c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return TEXT("");
}

void UActiveMQMapMessage::SetString(const FString& Name, const FString& Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::MapMessage>(InnerMessage)->setString(TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*Value));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}
