#include "MessageBus.h"


MessageBus::MessageBus(void)
{
}


MessageBus::~MessageBus(void)
{
}

MessageBus&
MessageBus::instance()
{
	static MessageBus instance;
	
	return instance;
}