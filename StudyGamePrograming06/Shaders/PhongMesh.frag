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

const int uDirLightNum = 2;
uniform sampler2D uTexture;
uniform vec3 uAmbientLight;
uniform DirectionalLight uDirLight[uDirLightNum];
uniform vec3 uCameraPos;
uniform float uSpecPower;

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
		L = normalize(-uDirLight[i].mDirection);
		R = normalize(reflect(-L, N));

		Diffuse = uDirLight[i].mDiffuseColor * max(0.0, dot(N, L));
		Specular = uDirLight[i].mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);
		lightColor += Diffuse + Specular;
	}
	outColor = texture(uTexture, fragTexCoord) * vec4(lightColor, 1.0);	
}