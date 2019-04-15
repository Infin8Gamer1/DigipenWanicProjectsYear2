#include "stdafx.h"
#include "ColorInverter.h"

// Systems
#include <ShaderProgram.h>

Effects::ColorInverter::ColorInverter() : PostEffect("colorInverter.frag"), invertTime(2.5)
{
	Initialize();
}

void Effects::ColorInverter::Initialize()
{
	timer = 0;
}

void Effects::ColorInverter::Update(float dt)
{
	timer += dt;
}

void Effects::ColorInverter::Draw()
{
	GetProgram().SetUniform("timer", timer);
	GetProgram().SetUniform("invertTime", invertTime);
}
