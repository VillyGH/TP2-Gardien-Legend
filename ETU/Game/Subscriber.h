#pragma once
#include "event.h"
struct Subscriber
{
	virtual void notify(Event event, const void* data) = 0;
};