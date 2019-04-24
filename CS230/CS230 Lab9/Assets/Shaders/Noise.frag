// Pixel shader for Fade To Black effect
#version 330 core

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D sourceTexture;

float hash(vec2 p) { return fract(1e4 * sin(17.0 * p.x + p.y * 0.1) * (0.1 + abs(sin(p.y * 13.0 + p.x)))); }

// 2D Noise based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = hash(i);
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));

    // Smooth Interpolation

	// Same code, with the clamps in smoothstep and common subexpressions
	// optimized away.
    vec2 u = f * f * (3.0 - 2.0 * f);

	return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

void main()
{
	// Normalized pixel coordinates (from 0 to 1)
	vec2 st = textureCoordinate;

    // Scale the coordinate system to see
    // some noise in action
    vec2 pos = vec2(st*20.0);

    // Use the noise function
    float n = noise(pos);

	// Get the color from the last render pass
	fragColor = texture2D(sourceTexture, textureCoordinate);

    fragColor *= vec4(vec3(n), 1.0);
}
