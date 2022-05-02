#include "stdafx.h"
#include "Publisher.h"
#include "Subscriber.h"

std::multimap<Event, std::reference_wrapper<Subscriber> >  Publisher::subscribers;
void Publisher::addSubscriber(Subscriber& o, Event e)
{
  auto t = std::make_pair(e, std::reference_wrapper<Subscriber> (o));
  subscribers.insert(t);
}

void Publisher::removeSubscriber(Subscriber& o, Event e)
{
  auto t = std::make_pair(e, std::reference_wrapper<Subscriber>(o));
  std::multimap<Event, std::reference_wrapper<Subscriber> >::iterator it = subscribers.equal_range(e).first;
  while (it != subscribers.equal_range(e).second)
  {
    if (&(it->second.get()) == &o && e==it->first)
    {
      subscribers.erase(it);
      break;
    }
    it++;
  }
}

void Publisher::notifySubscribers(Event event, const void * data)
{
  std::multimap<Event, std::reference_wrapper<Subscriber> >::iterator it = subscribers.equal_range(event).first;
  while( it != subscribers.equal_range(event).second)
  {
    it->second.get().notify(event,data);
    it++;
  }
}
     