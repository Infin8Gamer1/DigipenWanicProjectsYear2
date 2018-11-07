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
	playInReverse = false;

	sprite = spriteInput;
}

void Animation::Play(unsigned frameStartInput, unsigned frameCountInput, float frameDurationInput, bool isLoopingInput, bool playInReverseInput)
{
	//std::cout << "Animation::Play" << std::endl;

	frameStart = frameStartInput;
	frameIndex = frameStartInput;
	frameCount = frameCountInput;
	frameDelay = frameDurationInput;
	frameDuration = frameDurationInput;
	isLooping = isLoopingInput;
	playInReverse = playInReverseInput;

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
		if (playInReverse) {
			frameIndex--;
		} else {
			frameIndex++;
		}
		
		if (frameIndex >= frameCount || (frameIndex < 0 && playInReverse)) {
			if (isLooping) {
				frameIndex = frameStart;
				isDone = true;
				isRunning = true;
				sprite->SetFrame(frameIndex);
			} else {
				isDone = true;
				isRunning = false;
				sprite->SetFrame(frameStart);
			}
		} else {
			sprite->SetFrame(frameIndex);
		}

		
	}
}

bool Animation::IsDone() const
{
	return isDone;
}