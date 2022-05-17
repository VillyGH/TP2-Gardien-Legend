#pragma once
#include <map>
struct Subscriber;
#include "event.h"
class Publisher
{
public:
	static void addSubscriber(Subscriber& o, Event event);
	static void removeSubscriber(Subscriber& o, Event event);
	static void notifySubscribers(Event event, const void* data);

private:
	Publisher();
	Publisher(const Publisher&);
	Publisher& operator=(const Publisher&);
	static std::multimap<Event, std::reference_wrapper<Subscriber> >  subscribers;
};

