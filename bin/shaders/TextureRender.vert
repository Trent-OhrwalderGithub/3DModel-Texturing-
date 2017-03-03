#version 410
layout(location=0) in vec4 vertexPosition;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 vertexUV;

out vec2 UV;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vertexPosition;
	
	UV = vertexUV;
	UV.y = -UV.y;
}



