#include "stdafx.h"
#include "Event.h"

Event::Event(EventType type, const std::string & name, float delay, GUID sender, GUID receiver)
{
	this->type = type;
	this->name = name;
	this->delay = delay;
	this->sender = sender;
	this->receiver = receiver;
}

Event::~Event()
{
}
