#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in float visibility;

uniform sampler2D diffuse;
uniform vec3 skyColor;
void main()
{    
    vec4 texColor = texture(diffuse, TexCoords);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
	FragColor = mix(vec4(skyColor,1.0), FragColor, visibility);
}