#version 410
layout(location=0) in vec4 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

uniform mat4 projectViewMatrix;
uniform mat4 modelMatrix;

out vec3 colour;

void main()
{
	colour = vec3(1,1,1);
	mat4 PVM = projectViewMatrix * modelMatrix;
	
	gl_Position = PVM * position;
}



