// Fill out your copyright notice in the Description page of Project Settings.


#include "Messages/ActiveMQTextMessage.h"

THIRD_PARTY_INCLUDES_START
#include <cms/TextMessage.h>
THIRD_PARTY_INCLUDES_END

#include "ActiveMQExceptionHelper.h"

EActiveMQMessageType UActiveMQTextMessage::GetMessageType() const
{
	return EActiveMQMessageType::TextMessage;
}

FString UActiveMQTextMessage::GetText() const
{
	if (InnerMessage)
	{
		try
		{
			return UTF8_TO_TCHAR(StaticCastSharedPtr<cms::TextMessage>(InnerMessage)->getText().c_str());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message);
	}

	return TEXT("");
}

void UActiveMQTextMessage::SetText(const FString& InMessage)
{
	if (InnerMessage)
	{
		try
		{
			StaticCastSharedPtr<cms::TextMessage>(InnerMessage)->setText(TCHAR_TO_UTF8(*InMessage));
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetCMSMessageID(), EActiveMQExceptionOwnerType::EOT_Message);
	}
}
