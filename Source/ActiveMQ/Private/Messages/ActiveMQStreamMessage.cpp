// Fill out your copyright notice in the Description page of Project Settings.


#include "Messages/ActiveMQStreamMessage.h"

THIRD_PARTY_INCLUDES_START
#include "cms/StreamMessage.h"
THIRD_PARTY_INCLUDES_END

#include "ActiveMQExceptionHelper.h"

EActiveMQMessageType UActiveMQStreamMessage::GetMessageType() const
{
	return EActiveMQMessageType::StreamMessage;
}

EActiveMQMessageValueType UActiveMQStreamMessage::GetNextValueType() const
{
	if (InnerMessage)
	{
		try
		{
			return static_cast<EActiveMQMessageValueType>(StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->getNextValueType());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return EActiveMQMessageValueType::Unknown;
}

bool UActiveMQStreamMessage::readBoolean() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readBoolean();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return false;
}

void UActiveMQStreamMessage::writeBoolean(bool Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeBoolean(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

uint8 UActiveMQStreamMessage::ReadByte() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readByte();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQStreamMessage::WriteByte(uint8 Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeByte(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int32 UActiveMQStreamMessage::ReadBytes(TArray<uint8>& Bytes) const
{
	if (InnerMessage)
	{
		try
		{
			std::vector<uint8> Value;
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readBytes(Value);

			Bytes.SetNumUninitialized(Value.size());
			FMemory::Memcpy(Bytes.GetData(), Value.data(), Value.size());
			return Bytes.Num();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQStreamMessage::WriteBytes(const TArray<uint8>& Bytes)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeBytes(Bytes.GetData(), 0, Bytes.Num());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int32 UActiveMQStreamMessage::ReadBytes_WithLength(TArray<uint8>& Buffer, int32 Length) const
{
	if (InnerMessage)
	{
		try
		{
			if (Buffer.Num() < Length)
			{
				Buffer.SetNumZeroed(Length);
			}
			return StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readBytes(Buffer.GetData(), Length);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQStreamMessage::WriteBytes_WithParams(const TArray<uint8>& Buffer, int32 Offset, int32 Length)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeBytes(Buffer.GetData(), Offset, Length);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

char UActiveMQStreamMessage::ReadChar() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readChar();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQStreamMessage::WriteChar(char Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeChar(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

float UActiveMQStreamMessage::ReadFloat() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readFloat();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQStreamMessage::WriteFloat(float Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeFloat(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

double UActiveMQStreamMessage::ReadDouble() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readDouble();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0.0f;
}

void UActiveMQStreamMessage::WriteDouble(double Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeDouble(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

short UActiveMQStreamMessage::ReadShort() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readShort();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQStreamMessage::WriteShort(short Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeShort(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

unsigned short UActiveMQStreamMessage::ReadUnsignedShort() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readUnsignedShort();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQStreamMessage::WriteUnsignedShort(unsigned short Value)
{
}

int32 UActiveMQStreamMessage::ReadInt() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readInt();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQStreamMessage::WriteInt(int32 Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeInt(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int64 UActiveMQStreamMessage::ReadLong() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readLong();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQStreamMessage::WriteLong(int64 Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeLong(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

FString UActiveMQStreamMessage::ReadString() const
{
	if (InnerMessage)
	{
		try
		{
			std::shared_ptr<std::string> Value = StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->readString();
			return UTF8_TO_TCHAR(Value->c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return TEXT("");
}

void UActiveMQStreamMessage::WriteString(const FString& Value)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->writeString(TCHAR_TO_UTF8(*Value));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

void UActiveMQStreamMessage::Reset()
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::StreamMessage>(InnerMessage)->reset();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}
