#version 330

struct DirectionalLight
{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
};

in vec3 fragNormal;
in vec2 fragTexCoord;

const int uDirLightNum = 2;
uniform sampler2D uTexture;
uniform vec3 uAmbientLight;
uniform DirectionalLight uDirLight[uDirLightNum];

out vec4 outColor;

void main()
{
	vec3 N = normalize(fragNormal);
	vec3 lightColor = uAmbientLight;
	vec3 Diffuse;
	vec3 L;
		
	for (int i = 0; i < uDirLightNum; i++)
	{
		L = normalize(-uDirLight[i].mDirection);
	
		Diffuse = uDirLight[i].mDiffuseColor * max(0.0, dot(N, L));
		lightColor += Diffuse;
	}
	outColor = texture(uTexture, fragTexCoord) * vec4(lightColor, 1.0);	
}