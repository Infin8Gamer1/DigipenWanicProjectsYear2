//------------------------------------------------------------------------------
//
// File Name:	Event.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "stdafx.h"

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class EventHandler;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

enum EventType
{
	ET_Collision
};

struct Event
{
	// Constructor
	// Params:
	//  type = Type of the event.
	//  name = Name of the event; allows for sub-types.
	//  delay = How long to wait before sending this event.
	//  sender = GUID of the sending object.
	//  receiver = GUID of the receiving object (if none, all objects).
	Event(EventType type, const std::string& name, float delay = 0.0f, GUID sender = GUID(), GUID receiver = GUID());

	// Virtual destructor
	// Events should be dynamically allocated/destroyed if inheritance is used.
	virtual ~Event();

	// Event data, all publically
	// accessible for convenience.
	EventType type;
	std::string name;
	float delay;
	GUID sender;
	GUID receiver;
};

//------------------------------------------------------------------------------
