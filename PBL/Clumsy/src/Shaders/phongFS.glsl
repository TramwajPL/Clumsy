#version 330 core

in vec2 TexCoords;
in vec3 Normal;

out vec4 fragColor;


struct BaseLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform sampler2D texture_diffuse1;


uniform DirectionalLight directionalLight;

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal ,-direction); // attenuation 

	vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 0.0);

	if(diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;
	}

	return diffuseColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calcLight(directionalLight.base, -directionalLight.direction, normal);
}

void main()
{
	vec4 totalLight = vec4(ambientLight, 1.0);
	vec4 color = vec4(baseColor, 1.0);
	vec4 textureColor = texture(texture_diffuse1, TexCoords);

	if(textureColor != vec4(0.0,0.0,0.0,0.0))
	{
		color *= textureColor;
	}

	vec3 normal = normalize(Normal);
	totalLight += calcDirectionalLight(directionalLight, normal);

	fragColor = color * totalLight;
}