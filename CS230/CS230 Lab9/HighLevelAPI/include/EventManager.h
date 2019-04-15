//------------------------------------------------------------------------------
//
// File Name:	EventManager.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "BetaObject.h"
#include <vector>
#include <string>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// This is the base Event class. To create events with additional data,
// create additional event classes that inherit from this one.
struct Event
{
	// Constructor for Event
	// Params:
	//   type = The type of event that for which we are listening.
	Event(const std::string& type);

	const std::string type; // The type of event that for which we are listening.
};

// You are free to change the contents of this structure as long as you do not
//   change the public functions declared in the header.
class EventManager : public BetaObject
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// EventManager constructor
	EventManager();

	// EventManager destructor
	~EventManager();

	// Decreases timers on all delayed events, sends events that are ready.
	// Params:
	//   dt = The change in time since the previous frame.
	void Update(float dt) override;

	// Destroys all listeners and delayed events.
	void Shutdown() override;

	// Sends an event to all registered listeners.
	// Params:
	//	 event  = A pointer to the event being sent.
	//   source = The source of the event, typically a game object.
	//   delay  = How long to wait before sending the event.
	void SendEvent(const Event* event, const void* source, float delay = 0.0f);

	// Registers an event handler with the event manager. The handler will be called
	// when an event matching the given description is received.
	// Params:
	//   source		 = The source of the event, typically a game object.
	//   type		 = The type of event, e.g. "CollisionEvent".
	//   destination = The object that contains the event handler function.
	//   handler	 = The function that will be called when the event is received.
	template <class ObjectType>
	void RegisterEventHandler(const void* source, const std::string& type, ObjectType& destination,
		void (ObjectType::*handler)(const Event&))
	{
		listeners.push_back(new Listener<ObjectType>(source, type, destination, handler));
	}

	// Removes a registered event handler from the list of listeners in the event manager.
	// Params:
	//   source		 = The source of the event, typically a game object component.
	//   type		 = The type of event, e.g. "CollisionEvent".
	//   destination = The object that contains the event handler function.
	//   handler	 = The function that will be called when the event is received.
	template <class ObjectType>
	void UnregisterEventHandler(const void* source, const std::string& type, ObjectType& destination,
		void (ObjectType::*handler)(const Event&))
	{
		Listener<ObjectType> temp(source, type, destination, handler);

		// Find a listener that matches the given parameters.
		for(std::vector<ListenerBase*>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (temp == *(*it))
			{
				delete (*it);
				(*it) = nullptr;
			}
		}

		// Remove sent events
		if(listeners.size() != 0)
			listeners.erase(std::remove(listeners.begin(), listeners.end(), nullptr), listeners.end());
	}

private:
	//------------------------------------------------------------------------------
	// Private Structures:
	//------------------------------------------------------------------------------

	// An event that will be sent at a later time.
	struct DelayedEvent
	{
		// Constructor for DelayedEvent.
		// Params:
		//	 event  = A pointer to the event being sent.
		//   source = The source of the event, typically a game object component.
		//   delay  = How long to wait before sending the event.
		DelayedEvent(const Event* event, const void* source, float delay);

		const Event* event; // A pointer to the event being sent.
		const void* source; // The source of the event, typically a game object component.
		float delay;		// How long to wait before sending the event.
	};

	// Dummy base class for Listeners.
	struct ListenerBase
	{
		// Constructor for ListenerBase
		// Params:
		//   source = The source of the event, typically a game object component.
		//   type   = The type of event that for which we are listening.
		ListenerBase(const void* source, const std::string& type);

		// Calls an event handler and passes it an event.
		// Params:
		//	 event  = A pointer to the event being sent.
		virtual void CallHandler(const Event* event) const = 0;

		const void* source;		// The source of the event, typically a game object component.
		const std::string type; // The type of event that for which we are listening.
	};

	// Describes the conditions under which an event should be handled
	// and which handler should be called.
	template <class ObjectType>
	struct Listener : public ListenerBase
	{
		// Constructor for DelayedEvent.
		// Params:
		//	 event  = A pointer to the event being sent.
		//   source = The source of the event, typically a game object component.
		//   delay  = How long to wait before sending the event.
		Listener(const void* source, const std::string& type, ObjectType& destination,
			void (ObjectType::*handler)(const Event&))
			: ListenerBase(source, type), destination(destination), handler(handler)
		{
		}

		// Calls an event handler and passes it an event.
		// Params:
		//	 event = A pointer to the event being sent.
		void CallHandler(const Event* event) const
		{
			std::invoke(handler, destination, *event);
		}

		// Equality operator for listeners.
		// Params:
		//	 other = The other listener.
		bool operator==(const ListenerBase& other) const
		{
			const Listener<ObjectType>& otherObject = (const Listener<ObjectType>&)(other);

			if (source != otherObject.source) return false;
			if (type != otherObject.type) return false;
			if (&destination != &otherObject.destination) return false;
			if (handler != otherObject.handler) return false;
			return true;
		}

		ObjectType& destination;				   // The object that contains the event handler function.
		void (ObjectType::*handler)(const Event&); // The function that will be called when the event is received.
	};

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	std::vector<ListenerBase*> listeners; // List of all registered handlers/listeners.
	std::vector<DelayedEvent*> delayedEvents; // List of all events that have been delayed.
};

//------------------------------------------------------------------------------
