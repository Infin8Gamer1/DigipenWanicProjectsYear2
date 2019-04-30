//------------------------------------------------------------------------------
//
// File Name:	Texture.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Beta Engine
// Course:		WANIC VGP2
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Libs:
//------------------------------------------------------------------------------

#pragma comment(lib, "gdiplus.lib")

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Color.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

enum TextureFilterMode
{
	TM_Nearest,
	TM_Bilinear,
	TM_Trilinear
};

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Texture
{
public:
	//------------------------------------------------------------------------------
	// Public Functions
	//------------------------------------------------------------------------------

	// Creates a 1x1 white texture
	Texture();

	// Loads a texture from an array
	Texture(const std::vector<Color>& colors, unsigned width, unsigned height);

	// Destroys texture data via OpenGL
	~Texture();

	// Set this as the active texture
	// Params:
	//   uvOffset = The texture coordinate offset to use when rendering.
	void Use(const Vector2D& uvOffset = Vector2D()) const;

	// Returns the filename of the texture.
	const std::string& GetName() const;
	// Returns the ID of the texture buffer in OpenGL.
	unsigned GetBufferID() const;

	// Loads a texture from a file
	static Texture* CreateTextureFromFile(const std::string& filename, 
		TextureFilterMode mode = TM_Nearest);

	// The current relative path for loading textures
	static std::string texturePath;

private:
	//------------------------------------------------------------------------------
	// Private Functions
	//------------------------------------------------------------------------------
	
	// Deleted to prevent issues with pimpl.
	Texture(const Texture& rhs) = delete;
	Texture& operator=(const Texture& rhs) = delete;
	
	// Creates a texture with the given buffer ID and filename
	Texture(unsigned buffer, const std::string& name);

	// Loads a texture from an array
	void CreateTextureFromArray(const std::vector<Color>& colors, unsigned width, 
		unsigned height, TextureFilterMode mode = TM_Nearest);

	//------------------------------------------------------------------------------
	// Private Variables
	//------------------------------------------------------------------------------

	unsigned bufferID;
	std::string filename;
};

//------------------------------------------------------------------------------
