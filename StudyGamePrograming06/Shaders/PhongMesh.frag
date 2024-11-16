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
in mat4 fragWorldTransform;

const int uDirLightNum = 2;
const int uPointLightNum = 4;
uniform sampler2D uTexture;
uniform vec3 uAmbientLight;
uniform DirectionalLight uDirLight[uDirLightNum];
uniform vec3 uCameraPos;
uniform float uSpecPower;
uniform PointLight uPointLight[uPointLightNum];

out vec4 outColor;

void main()
{
	vec3 N = normalize(fragNormal);
	vec3 V = normalize(uCameraPos - fragWorldPos);
	vec3 lightColor = uAmbientLight;
	vec3 Diffuse;
	vec3 Specular;
	vec3 L;
	vec3 R;
		
	for (int i = 0; i < uDirLightNum; i++)
	{
		if (length(uDirLight[i].mDirection) > 0)
		{
			L = normalize(-uDirLight[i].mDirection);
			R = normalize(reflect(-L, N));

			Diffuse = uDirLight[i].mDiffuseColor * max(0.0, dot(N, L));
			Specular = uDirLight[i].mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);
			lightColor += Diffuse + Specular;
		}
	}
	
	vec4 pos;
	vec3 pPos;
	vec3 pDir;
	float pLen;
	float pAtt;
	for (int i = 0; i < uPointLightNum; i++)
	{
		if (uPointLight[i].mAttenuation > 0)
		{
			pos = vec4(uPointLight[i].mPosition, 1.0);
			pPos = pos.xyz;
			pDir = pPos - fragWorldPos;
			pLen = length(pDir) * 0.001;
			pAtt = 1.0 / (uPointLight[i].mAttenuation * pLen * pLen);
			L = normalize(pDir);
			R = normalize(reflect(-L, N));
			Diffuse = uPointLight[i].mDiffuseColor * max(0.0, dot(N, L));
			Specular = uPointLight[i].mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);
			lightColor += pAtt * (Diffuse + Specular);
		}		
	}

	outColor = texture(uTexture, fragTexCoord) * vec4(lightColor, 1.0);	
}