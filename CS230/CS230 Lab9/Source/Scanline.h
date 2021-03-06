//------------------------------------------------------------------------------
//
// File Name:	Noise.h
// Author(s):	Jacob Holyfield
// Project:		Beta Engine
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <PostEffect.h>

//------------------------------------------------------------------------------

namespace Effects
{
	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	class Scanline : public PostEffect
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		Scanline();

		// Send data to OpenGL
		void Draw() override;

	private:
		//------------------------------------------------------------------------------
		// Private Data:
		//------------------------------------------------------------------------------

		
	};
}

//------------------------------------------------------------------------------
