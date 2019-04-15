#version 330 core

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D sourceTexture;

uniform float timer;			// Time elapsed since effect started.
uniform float invertTime;	// Time it takes to go from unaltered color to inverted.

// Precise method, which guarantees v = v1 when t = 1.
float lerp(float v0, float v1, float t) {
	return (1 - t) * v0 + t * v1;
}

void main()
{
    fragColor = texture2D(sourceTexture, textureCoordinate);

	float myTimer = timer;

	if (myTimer >= invertTime)
	{
		myTimer = invertTime;
	}

	float newR = lerp(fragColor.r, 1.0 - fragColor.r, myTimer / invertTime);
	float newG = lerp(fragColor.g, 1.0 - fragColor.g, myTimer / invertTime);
	float newB = lerp(fragColor.b, 1.0 - fragColor.b, myTimer / invertTime);

	fragColor = vec4(newR, newG, newB, fragColor.a);
}
