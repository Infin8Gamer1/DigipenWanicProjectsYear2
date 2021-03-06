//------------------------------------------------------------------------------
//
// File Name:	SoundManager.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Project 7
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "BetaObject.h"
#include <fmod_studio.hpp>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

using FMOD::Studio::EventInstance;

// Undefining Windows macro 
#ifdef PlaySound
#undef PlaySound
#endif

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public functions declared in the header.
class SoundManager : public BetaObject
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor - initializes FMOD.
	SoundManager();

	// Destructor
	~SoundManager();

	// Update the FMOD system.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt);

	// Shutdown the sound manager.
	void Shutdown(void);

	// Creates a non-looping FMOD sound.
	// Params:
	//	 filename = Name of the sound file (WAV).
	void AddEffect(const std::string& filename);

	// Creates an FMOD stream for a music file.
	// Params:
	//	 filename = Name of the music file (MP3).
	void AddMusic(const std::string& filename);

	// Creates an FMOD sound bank
	// Params:
	//   filename = Name of the FMOD bank file.
	void AddBank(const std::string& filename);

	// Unloads a sound file from memory.
	void RemoveSound(const std::string& filename);

	// Plays a sound with the specified name.
	// Params:
	//	 name = The name of the sound to be played.
	void PlaySound(const std::string& name);

	// Starts an audio event with the given name.
	// The event must be in one of the loaded banks.
	// Params:
	//	 name = The name of the event that will be started.
	EventInstance* PlayEvent(const std::string& name);

	// Set the volume of the music channel.
	// Params:
	//	 volume = New value for the music volume (0.0 to 1.0).
	void SetMusicVolume(float volume);

	// Set the volume of the sound effects channel group.
	// Params:
	//	 volume = New value for the FX volume (0.0 to 1.0).
	void SetEffectsVolume(float volume);

	// Get the volume of the music channel.
	// Return:
	//	 volume = Current value for the music volume.
	float GetMusicVolume() const;

	// Get the volume of the sound effects channel group.
	// Return:
	//	 volume = Current value for the FX volume.
	float GetEffectsVolume() const;

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Different behaviors for SFX vs BGM
	void PlayEffect(FMOD::Sound* sound) const;
	void PlayMusic(FMOD::Sound* sound);

	// Add FX/BGM helper
	void AddSound(const std::string& filename, FMOD_MODE mode);

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	std::vector<FMOD::Sound*> soundList;		// List of all loaded sounds
	std::vector<FMOD::Studio::Bank*> bankList;  // List of all loaded sound banks.
	FMOD::Channel* musicChannel;			 // The channel most recently used to play music
	FMOD::ChannelGroup* effectsChannelGroup; // The channel group used for SFX.
	FMOD::System *system;					 // The internal FMOD low-level system
	FMOD::Studio::System *studioSystem;		 // The internal FMOD studio system.
	float musicVolume;	 // The current volume of the music channel (0.0 to 1.0).
	float effectsVolume; // The current volume of the sound effects channel group (0.0 to 1.0).

	std::string audioFilePath;
};
//------------------------------------------------------------------------------
