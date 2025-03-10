// Fill out your copyright notice in the Description page of Project Settings.


#include "Messages/ActiveMQMessageEnumeration.h"

#include "ActiveMQExceptionHelper.h"

THIRD_PARTY_INCLUDES_START
#include "cms/MessageEnumeration.h"
THIRD_PARTY_INCLUDES_END

void UActiveMQMessageEnumeration::SetInnerEnumeration(const TSharedPtr<cms::MessageEnumeration>& NewEnumeration)
{
	InnerEnumeration = NewEnumeration;
}

const TSharedPtr<cms::MessageEnumeration>& UActiveMQMessageEnumeration::GetInnerEnumeration() const
{
	return InnerEnumeration;
}

bool UActiveMQMessageEnumeration::HasMoreMessages()
{
	if (InnerEnumeration)
	{
		try
		{
			return InnerEnumeration->hasMoreMessages();
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_MessageEnumeration)
	}

	return false;
}

UActiveMQMessage* UActiveMQMessageEnumeration::NextMessage()
{
	UActiveMQSubsystem* Subsystem = GetWorld()->GetSubsystem<UActiveMQSubsystem>();
	if (InnerEnumeration && Subsystem != nullptr)
	{
		try
		{
			return Subsystem->ConvertCMSMessageToUEMessage(GetOuter(), InnerEnumeration->nextMessage());
		}
		ACTIVEMQ_EXCEPTION_DELIVER_END(GetName(), EActiveMQExceptionOwnerType::EOT_MessageEnumeration)
	}

	return nullptr;
}
