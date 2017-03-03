#version 410

in vec3 colour;
in vec2 UV;

out vec4 fragColour;

uniform sampler2D myTextureSampler;

void main()
{
	vec4 diffuseSampler2D = texture(myTextureSampler, UV);
	fragColour = diffuseSampler2D;
}