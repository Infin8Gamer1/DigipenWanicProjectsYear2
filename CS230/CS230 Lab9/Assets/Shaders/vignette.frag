#version 330 core

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D sourceTexture;

uniform float ScreenX;
uniform float ScreenY;

void main()
{
	
	vec2 ret = vec2(textureCoordinate.x / ScreenX, (ScreenY - textureCoordinate.y) / ScreenY);// ret is now 0-1 in both dimensions

	//calculate vignette ammount
	float vignetteAmt;

	vec2 vignetteCenter = vec2(0.5, 0.5);
	vignetteAmt = 1.0 - distance(ret, vignetteCenter);
    vignetteAmt = 0.03 + pow(vignetteAmt, 0.15);// strength
    vignetteAmt = clamp(vignetteAmt, 0.0,1.0);

	fragColor = vec4(1.0,1.0,1.0,1.0);//texture2D(sourceTexture, textureCoordinate);

	//add vignette
	fragColor *= vignetteAmt;
}
