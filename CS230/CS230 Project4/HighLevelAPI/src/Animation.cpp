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
#include "GameObject.h"
#include <SpriteSource.h>

Animation::Animation() : Component("Animation")
{
	frameIndex = 0;
	
	frameDelay = 0;

	frameDuration = 20;

	isRunning = false;
	isLooping = false;
	isDone = false;
	playInReverse = false;

	sprite = nullptr;

	lastSpriteSource = nullptr;
}

Component * Animation::Clone() const
{
	Animation* out = new Animation();

	//out->sprite = sprite;

	return out;
}

void Animation::Initialize()
{
	sprite = GetOwner()->GetComponent<Sprite>();

	lastSpriteSource = sprite->GetSpriteSource();
}

void Animation::Play(float frameDurationInput, bool isLoopingInput, bool playInReverseInput)
{
	//std::cout << "Animation::Play" << std::endl;

	lastSpriteSource = sprite->GetSpriteSource();

	frameIndex = sprite->GetSpriteSource()->GetFrameStart();

	frameDelay = frameDurationInput;
	frameDuration = frameDurationInput;
	isLooping = isLoopingInput;
	playInReverse = playInReverseInput;

	isRunning = true;
	isDone = false;

	GetOwner()->GetComponent<Sprite>()->SetFrame(frameIndex);
}

void Animation::FixedUpdate(float dt)
{
	//std::cout << "Animation::FixedUpdate" << std::endl;
	if (lastSpriteSource != sprite->GetSpriteSource()) {
		lastSpriteSource = sprite->GetSpriteSource();
		Play(frameDuration, isLooping, playInReverse);
	}

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
		
		if (frameIndex >= sprite->GetSpriteSource()->GetFrameCount() || (frameIndex < 0 && playInReverse)) {
			if (isLooping) {
				frameIndex = sprite->GetSpriteSource()->GetFrameStart();
				isDone = true;
				isRunning = true;
				sprite->SetFrame(frameIndex);
			} else {
				isDone = true;
				isRunning = false;
				sprite->SetFrame(sprite->GetSpriteSource()->GetFrameStart());
			}
		} else {
			sprite->SetFrame(frameIndex);
		}
		frameDelay = frameDuration;
	}
}

bool Animation::IsDone() const
{
	return isDone;
}

void Animation::SetFrameDuration(float duration)
{
	frameDuration = duration;
}
