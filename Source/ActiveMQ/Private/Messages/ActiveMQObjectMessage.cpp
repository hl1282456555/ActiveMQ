// Fill out your copyright notice in the Description page of Project Settings.


#include "Messages/ActiveMQObjectMessage.h"

THIRD_PARTY_INCLUDES_START
#include "cms/ObjectMessage.h"
THIRD_PARTY_INCLUDES_END

#include "ActiveMQExceptionHelper.h"

EActiveMQMessageType UActiveMQObjectMessage::GetMessageType() const
{
	return EActiveMQMessageType::ObjectMessage;
}

TArray<uint8> UActiveMQObjectMessage::GetObjectBytes() const
{
	TArray<uint8> OutBytes;
	if (InnerMessage)
    	{
    		try
    		{
    			std::vector<uint8> Bytes = StaticCastSharedPtr<cms::ObjectMessage>(InnerMessage)->getObjectBytes();
    			OutBytes.SetNumUninitialized(Bytes.size());
    			FMemory::Memcpy(OutBytes.GetData(), Bytes.data(), Bytes.size());
    		}
    		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message);
    	}

	return OutBytes;
}

void UActiveMQObjectMessage::SetObjectBytes(const TArray<uint8>& InBytes)
{
	if (InnerMessage)
	{
		try
		{
			std::vector<uint8> Bytes(InBytes.Num(), 0);
			FMemory::Memcpy(Bytes.data(), InBytes.GetData(), InBytes.Num());
			StaticCastSharedPtr<cms::ObjectMessage>(InnerMessage)->setObjectBytes(Bytes);
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message);
	}
}
