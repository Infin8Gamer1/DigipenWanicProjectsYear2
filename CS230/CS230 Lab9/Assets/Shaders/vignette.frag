#version 330 core

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D sourceTexture;

void main()
{
	
	vec2 ret = textureCoordinate;

	//calculate vignette ammount
	float vignetteAmt;

	vec2 vignetteCenter = vec2(0.5, 0.5);
	vignetteAmt = 1.0 - distance(ret, vignetteCenter);
    vignetteAmt = 0.03 + pow(vignetteAmt, 0.25);// strength
    vignetteAmt = clamp(vignetteAmt, 0.0,1.0);

	fragColor = texture2D(sourceTexture, textureCoordinate); //vec4(1.0,1.0,1.0,1.0);

	//add vignette
	fragColor *= vignetteAmt;
}
