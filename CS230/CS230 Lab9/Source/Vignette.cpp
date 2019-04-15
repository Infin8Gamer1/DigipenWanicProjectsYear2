#include "stdafx.h"
#include "Vignette.h"

// Systems
#include <ShaderProgram.h>
#include <Graphics.h>

Effects::Vignette::Vignette() : PostEffect("vignette.frag")
{
	Initialize();
}

void Effects::Vignette::Initialize()
{
	screenSize = Graphics::GetInstance().GetViewport();
}

void Effects::Vignette::Draw()
{
	GetProgram().SetUniform("ScreenX", screenSize.x);
	GetProgram().SetUniform("ScreenY", screenSize.y);
}
