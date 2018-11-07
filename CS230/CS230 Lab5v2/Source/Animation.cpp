//------------------------------------------------------------------------------
//
// File Name:	Animation.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Animation.h"
#include "Sprite.h"

Animation::Animation(Sprite * spriteInput)
{
	frameIndex = 0;
	frameCount = 0;
	frameStart = 0;
	
	frameDelay = 0;
	frameDuration = 20;

	isRunning = false;
	isLooping = false;
	isDone = false;

	sprite = spriteInput;
}

void Animation::Play(unsigned frameStartInput, unsigned frameCountInput, float frameDurationInput, bool isLoopingInput)
{
	//std::cout << "Animation::Play" << std::endl;

	frameStart = frameStartInput;
	frameIndex = frameStartInput;
	frameCount = frameCountInput;
	frameDelay = frameDurationInput;
	frameDuration = frameDurationInput;
	isLooping = isLoopingInput;

	isRunning = true;
	isDone = false;

	sprite->SetFrame(frameIndex);
}

void Animation::Update(float dt)
{
	//std::cout << "Animation::Update" << std::endl;

	isDone = false;

	if (!isRunning) {
		return;
	}

	frameDelay -= dt;

	if (frameDelay <= 0.0f) {
		frameIndex++;
		if (frameIndex >= frameCount) {
			if (isLooping) {
				frameIndex = frameStart;
				isDone = true;
				isRunning = true;
			} else {
				isDone = true;
				isRunning = false;
			}
		}

		sprite->SetFrame(frameIndex);
	}
}

bool Animation::IsDone() const
{
	return isDone;
}