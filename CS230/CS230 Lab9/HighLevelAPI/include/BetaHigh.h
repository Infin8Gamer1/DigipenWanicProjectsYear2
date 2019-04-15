//------------------------------------------------------------------------------
//
// File Name:	BetaHigh.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

// Dependencies
#ifdef _M_IX86
	#ifdef _DEBUG
		#pragma comment(lib, "BetaHigh_x86_D.lib")
	#else
		#pragma comment(lib, "BetaHigh_x86.lib")
	#endif
#else
	#ifdef _DEBUG
		#pragma comment(lib, "BetaHigh_x64_D.lib")
	#else
		#pragma comment(lib, "BetaHigh_x64.lib")
	#endif
#endif

// Levels and Objects
#include <BetaHighLevels.h>
#include <BetaHighObjects.h>
#include <BetaHighSerialization.h>

// Systems and Resources
#include <BetaLowEngine.h>
#include <BetaHighGraphics.h>
#include <BetaHighAudio.h>
#include <BetaHighEvents.h>

// Physics and Collisions
#include <BetaHighCollisions.h>
#include <BetaHighPhysics.h>

// Utility
#include <BetaHighMath.h>

//------------------------------------------------------------------------------
