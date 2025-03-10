#include "ActiveMQExceptionHelper.h"

void DeliverException(const UObject* Context, const FString& Owner, EActiveMQExceptionOwnerType OwnerType,
	const cms::CMSException& Exception)
{
	UActiveMQSubsystem* Subsystem = Context->GetWorld()->GetSubsystem<UActiveMQSubsystem>();
	if (Subsystem != nullptr)
	{
		Subsystem->DispatchExceptionMessage(Owner, OwnerType, UTF8_TO_TCHAR(Exception.what()));
	}
}
