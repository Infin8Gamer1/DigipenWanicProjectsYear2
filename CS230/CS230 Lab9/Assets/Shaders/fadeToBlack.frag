// Pixel shader for Fade To Black effect
#version 330 core

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D sourceTexture;

uniform float timer;			// Current time in fade. Starts at effectDuration and decreases.
uniform float effectDuration;	// Duration of the fade

void main()
{
	// Get the color from the last render pass
	fragColor = texture2D(sourceTexture, textureCoordinate);

	// If the effect duration isn't up
	if(timer > 0.0)
	{
		// Change color so it's closer to 0.0 (no color; black)
		fragColor *= timer / effectDuration;
	}
	// Else, it's just black
	else fragColor *= 0.0;
}
