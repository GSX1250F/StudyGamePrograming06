#version 330

in vec2 fragTexCoord;

uniform sampler2D uTexture;
uniform vec3 uAmbientLight;

out vec4 outColor;

void main()
{
	vec3 lightColor = uAmbientLight;
	
	outColor = texture(uTexture, fragTexCoord) * vec4(lightColor, 1.0);	
}