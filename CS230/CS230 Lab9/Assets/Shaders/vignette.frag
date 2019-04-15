#version 330 core

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D sourceTexture;

uniform float ScreenX;
uniform float ScreenY;

void main()
{
    fragColor = texture2D(sourceTexture, textureCoordinate);

	vec2 uv = vec2(fragCoord.x / ScreenX, fragCoord.y / ScreenY);
   
    uv *=  1.0 - uv.yx;
    
    float vig = uv.x*uv.y * 15.0;
    
    vig = pow(vig, 0.25);
    
    fragColor = vec4(vig); 
}
