#pragma once

#include "CoreMinimal.h"
#include "ActiveMQSubsystem.h"

THIRD_PARTY_INCLUDES_START
#include <cms/CMSException.h>
THIRD_PARTY_INCLUDES_END

ACTIVEMQ_API void DeliverException(const UObject* Context, const FString& Owner, EActiveMQExceptionOwnerType OwnerType, const cms::CMSException& Exception);

#define ACTIVEMQ_EXCEPTION_DELIVER_END(Owner, OwnerType) catch(const cms::CMSException& e){ DeliverException(this, Owner, OwnerType, e); }
