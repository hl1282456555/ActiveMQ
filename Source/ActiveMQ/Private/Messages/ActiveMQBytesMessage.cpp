// Fill out your copyright notice in the Description page of Project Settings.


#include "Messages/ActiveMQBytesMessage.h"

THIRD_PARTY_INCLUDES_START
#include "cms/BytesMessage.h"
THIRD_PARTY_INCLUDES_END

#include "ActiveMQExceptionHelper.h"

EActiveMQMessageType UActiveMQBytesMessage::GetMessageType() const
{
	return EActiveMQMessageType::BytesMessage;
}

void UActiveMQBytesMessage::SetBodyBytes(const TArray<uint8>& InBodyBytes)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->setBodyBytes(InBodyBytes.GetData(), InBodyBytes.Num());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

TArray<uint8> UActiveMQBytesMessage::GetBodyBytes() const
{
	TArray<uint8> Result;
	if (InnerMessage)
	{
		try
		{
			int32 BodyLength = StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->getBodyLength();
			Result.SetNumUninitialized(BodyLength);
			
			unsigned char* BodyBytes = StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->getBodyBytes();
			FMemory::Memcpy(Result.GetData(), BodyBytes, BodyLength);

			delete[] BodyBytes;
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return Result;
}

int32 UActiveMQBytesMessage::GetBodyLength() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->getBodyLength();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQBytesMessage::Reset()
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->reset();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

bool UActiveMQBytesMessage::ReadBoolean() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readBoolean();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return false;
}

void UActiveMQBytesMessage::WriteBoolean(bool Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeBoolean(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

uint8 UActiveMQBytesMessage::ReadByte() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readByte();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQBytesMessage::WriteByte(uint8 Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeByte(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int32 UActiveMQBytesMessage::ReadBytes(TArray<uint8>& Bytes) const
{
	if (InnerMessage)
	{
		try
		{
			std::vector<uint8> BytesInMessage;
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readBytes(BytesInMessage);

			Bytes.SetNumUninitialized(BytesInMessage.size());
			FMemory::Memcpy(Bytes.GetData(), BytesInMessage.data(), BytesInMessage.size());
			return Bytes.Num();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
	
	return 0;
}

void UActiveMQBytesMessage::WriteBytes(const TArray<uint8>& InBytes) const
{
	if (InnerMessage)
	{
		try
		{
			std::vector<uint8> BytesForWrite(InBytes.GetData(), InBytes.GetData() + InBytes.Num());
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeBytes(BytesForWrite);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int32 UActiveMQBytesMessage::ReadBytes_WithLength(TArray<uint8>& Buffer, int32 Length) const
{
	if (InnerMessage)
	{
		try
		{
			if (Buffer.Num() < Length)
			{
				Buffer.SetNumZeroed(Length);
			}
			
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readBytes(Buffer.GetData(), Length);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQBytesMessage::WriteBytes_WithParams(const TArray<uint8>& InBytes, int32 Offset, int32 Length) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeBytes(InBytes.GetData(), Offset, Length);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

char UActiveMQBytesMessage::ReadChar() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readChar();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQBytesMessage::WriteChar(char Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeChar(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

float UActiveMQBytesMessage::ReadFloat() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readFloat();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0.0f;
}

void UActiveMQBytesMessage::WriteFloat(float Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeFloat(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

double UActiveMQBytesMessage::ReadDouble() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readDouble();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0.0;
}

void UActiveMQBytesMessage::WriteDouble(double Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeDouble(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

short UActiveMQBytesMessage::ReadShort() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readShort();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQBytesMessage::WriteShort(short Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeShort(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

unsigned short UActiveMQBytesMessage::ReadUnsignedShort() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readUnsignedShort();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQBytesMessage::WriteUnsignedShort(unsigned short Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeUnsignedShort(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int32 UActiveMQBytesMessage::ReadInt() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readInt();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQBytesMessage::WriteInt(int32 Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeInt(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

int64 UActiveMQBytesMessage::ReadLong() const
{
	if (InnerMessage)
	{
		try
		{
			return StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readLong();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return 0;
}

void UActiveMQBytesMessage::WriteLong(int64 Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeLong(Value);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

FString UActiveMQBytesMessage::ReadString() const
{
	FString Result;
	if (InnerMessage)
	{
		try
		{
			std::shared_ptr<std::string> Value = StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readString();
			Result = UTF8_TO_TCHAR(Value->c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return Result;
}

void UActiveMQBytesMessage::WriteString(const FString& Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeString(TCHAR_TO_UTF8(*Value));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}

FString UActiveMQBytesMessage::ReadUTF() const
{
	FString Result;
	if (InnerMessage)
	{
		try
		{
			std::shared_ptr<std::string> UTFValue = StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->readUTF();
			Result = UTF8_TO_TCHAR(UTFValue->c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}

	return Result;
}

void UActiveMQBytesMessage::WriteUTF(const FString& Value) const
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::BytesMessage>(InnerMessage)->writeUTF(TCHAR_TO_UTF8(*Value));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message)
	}
}
