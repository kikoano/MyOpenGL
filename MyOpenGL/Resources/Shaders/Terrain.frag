#version 330 core
out vec4 FragColor;

struct Material{
	sampler2D diffuse;
	sampler2D diffuse2;
	sampler2D blendMap;
	sampler2D specular;
	float shininess;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;  
in vec3 FragPos;  
in float visibility;

  
uniform vec3 viewPos; 
uniform Material material;
uniform Light light;
uniform int scaleTiles;
uniform vec3 skyColor;

void main()
{
	// Tiled Texture Coords
	vec2 tiledCoords = TexCoords * scaleTiles;
	vec3 norm = normalize(Normal);

	// blendTextures
	vec3 blendMap = texture2D(material.blendMap, TexCoords).rgb;

	vec3 texel0 = texture2D(material.diffuse, tiledCoords).rgb;
    vec3 texel1 = texture2D(material.diffuse2, tiledCoords).rgb;
  
	//float a = clamp((norm.y - .6)*5 + .5, 0, 0.7);
	//diffuseBlend = mix(texel1, texel0, a);
	vec3 diffuseBlend = mix(texel0,texel1,blendMap.g).rgb;

	// ambient
	vec3 ambient = light.ambient * diffuseBlend;
	
	// diffuse
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * diffuseBlend);
	
	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);
	vec3 specular = light.specular * (spec * (blendMap/4));
	
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
	FragColor = mix(vec4(skyColor,1.0), FragColor, visibility);
} 

