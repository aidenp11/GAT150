#pragma once
#include "Event.h"
#include "Framework/Singleton.h"
#include <map>
#include <list>
#include <functional>

namespace lady
{
	class IEventListener
	{
		//
	};

	class EventManager : public Singleton<EventManager>
	{
	public:
		using eventFunc = std::function<void(const Event&)>;

		struct EventDispatcher
		{
			IEventListener* listener = nullptr; // object that can listen for events
			eventFunc function; // function that is called on event
		};

	public:
		void Update(float dt);

		void Subscribe(Event::id_t id, IEventListener* listener, eventFunc function);
		void Unsubscribe(Event::id_t id, IEventListener* listener);

		void DispatchEvent(Event::id_t id, Event::data_t data);

		friend class Singleton;

	public:
		EventManager() = default;

	private:
		std::map<Event::id_t, std::list<EventDispatcher>> m_dispatchers;


	};
}
