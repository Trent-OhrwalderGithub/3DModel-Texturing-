#pragma once

#include <gl_core_4_4.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include "GeometryHelper.h"	
#include <vector>


struct OpenGLInfo
{
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_faceCount;
};

struct OBJVertex
{
	glm::vec4 position;
	glm::vec3 normal;
	glm::vec2 uv;
};


class RenderModel
{

public:

	//tinyobj::attrib_t attributes;
	//std::vector<tinyobj::shape_t> shapes;
	//std::vector<tinyobj::material_t> materials;
	//std::string err;
	//bool success = tinyobj::LoadObj(&attributes, &shapes, &materials,
	//	&err, "./models/stanford/Lucy.obj");



	static std::vector<RenderData*> LoadOBJFromDisk(std::string path);

protected:



private:



};