#include "RenderData.h"
#include <gl_core_4_4.h>
#include <assert.h>

RenderData::RenderData()
	: m_VAO(-1)
	, m_VBO(-1)
	, m_IBO(-1)
	, m_numberOfIndicies(0)
	, hasIndexBuffer(true)
{
}

RenderData::~RenderData()
{
	if (m_IBO != -1)
	glDeleteBuffers(1, &m_IBO);
	if (m_VBO != -1)
	glDeleteBuffers(1, &m_VBO);
	if (m_VAO != -1)
	glDeleteVertexArrays(1, &m_VAO);
}

RenderData::RenderData(RenderData && other)
{
	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
	m_IBO = other.m_IBO;
	m_numberOfIndicies = other.m_numberOfIndicies;
	hasIndexBuffer = other.hasIndexBuffer;

	other.m_VAO = -1;
	other.m_VBO = -1;
	other.m_IBO = -1;
}


void RenderData::GenerateBuffers(bool generateIndexBuffer)
{
	assert(m_VAO == -1);
	assert(m_VBO == -1);
	assert(m_IBO == -1);

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	if (generateIndexBuffer) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBindVertexArray(0);

	hasIndexBuffer = generateIndexBuffer;
}

void RenderData::Render() const
{
	Bind();
	if (hasIndexBuffer)
	{
		glDrawElements(GL_TRIANGLES, m_numberOfIndicies,
		GL_UNSIGNED_INT, 0);
	}	
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_numberOfIndicies);
	}

	Unbind();
}


void RenderData::Bind() const
{
	assert(m_VAO != -1);
	glBindVertexArray(m_VAO);
}
void RenderData::Unbind() const
{
	glBindVertexArray(0);
}

