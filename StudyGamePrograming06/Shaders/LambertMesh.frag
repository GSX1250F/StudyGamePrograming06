#version 330

struct DirectionalLight
{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
};

struct PointLight
{
	float mAttenuation;
	vec3 mPosition;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
};

in vec3 fragWorldPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

const int uDirLightNum = 2;
const int uPointLightNum = 4;
uniform sampler2D uTexture;
uniform vec3 uAmbientLight;
uniform DirectionalLight uDirLights[uDirLightNum];
uniform PointLight uPointLights[uPointLightNum];

out vec4 outColor;

void main()
{
	vec3 N = normalize(fragNormal);
	vec3 lightColor = uAmbientLight;
	vec3 Diffuse;
	vec3 L;
		
	for (int i = 0; i < uDirLightNum; i++)
	{
		if (length(uDirLights[i].mDirection) > 0)
		{
			L = normalize(-uDirLights[i].mDirection);
	
			Diffuse = uDirLights[i].mDiffuseColor * max(0.0, dot(N, L));
			lightColor += Diffuse;
		}
	}

	vec3 pDir;
	float pLen;
	float pAtt;
	for (int i = 0; i < uPointLightNum; i++)
	{
		if (uPointLights[i].mAttenuation > 0)
		{
			pDir = uPointLights[i].mPosition - fragWorldPos;
			pLen = length(pDir) * 0.001;
			pAtt = 1.0 / (uPointLights[i].mAttenuation * pLen * pLen);
			L = normalize(pDir);
			Diffuse = uPointLights[i].mDiffuseColor * max(0.0, dot(N, L));
			lightColor += pAtt * Diffuse;
		}		
	}

	outColor = texture(uTexture, fragTexCoord) * vec4(lightColor, 1.0);	
}