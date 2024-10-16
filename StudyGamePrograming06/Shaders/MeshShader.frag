#version 330

struct DirectionalLight
{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
};

in vec3 fragWorldPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform sampler2D uTexture;
uniform vec3 uAmbientLight;
uniform DirectionalLight uDirLight;
uniform vec3 uCameraPos;
uniform float uSpecPower;

out vec4 outColor;

void main()
{
	vec3 N = normalize(fragNormal);
    vec3 L = normalize(-uDirLight.mDirection);
	vec3 V = normalize(uCameraPos - fragWorldPos);
	vec3 R = normalize(reflect(-L, N));

	vec3 ka = uAmbientLight;
	vec3 kd = uDirLight.mDiffuseColor;
	vec3 ks = uDirLight.mSpecColor;

	vec3 lightColor = ka;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		lightColor += kd * NdotL;
	}
	float RdotV = dot(R, V);
	if (RdotV > 0)
	{
		lightColor += ks * RdotV;
	}
	
	//outColor = texture(uTexture, fragTexCoord);	
	outColor = texture(uTexture, fragTexCoord) * vec4(lightColor, 1.0);	
}