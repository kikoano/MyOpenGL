#version 330 core
struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
unifrom Material material;


out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	// ambient
   vec3 ambient = lightColor * material.ambient;

   // diffuse
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);
   float diff = max(dot(norm, lightDIr), 0.0f);
   vec3 diffuse = lightColor * (diff * material.diffuse);

   // specular
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir =
} 

