// Pixel shader for Fade To Black effect
#version 330 core

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D sourceTexture;

void main()
{
	// Get the color from the last render pass
	fragColor = texture2D(sourceTexture, textureCoordinate);

	// scanline
	float scanline = sin(textureCoordinate.y*800.0)*0.04;
	fragColor -= scanline;
}
