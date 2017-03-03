#include "TextureRender.h"
#include <gl_core_4_4.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


TextureRender::TextureRender(std::string filePath)
	: m_textureID(-1)
	, m_normalMap(-1)
	, m_specularMap(-1)
	, m_textureWidth(0)
	, m_textureHeight(0)
	, m_textureFormat(0)
	, m_texturePath(filePath)
{
	LoadTexture(m_textureID);
	LoadTexture(m_normalMap);
	LoadTexture(m_specularMap);
}

TextureRender::~TextureRender()
{
	if (m_textureID != -1)
	{
		glDeleteTextures(1, &m_textureID);
	}
	if (m_normalMap != -1)
	{
		glDeleteTextures(1, &m_normalMap);
	}
	if (m_specularMap != -1)
	{
		glDeleteTextures(1, &m_specularMap);
	}
}

TextureRender::TextureRender(TextureRender && other)
{
	m_textureID = other.m_textureID;
	m_normalMap = other.m_normalMap;
	m_specularMap = other.m_specularMap;
	m_textureWidth = other.m_textureWidth;
	m_textureHeight = other.m_textureHeight;
	m_textureFormat = other.m_textureFormat;
	m_texturePath = other.m_texturePath;

	other.m_textureID = -1;
}

void TextureRender::LoadTexture(unsigned int& a_ID)
{
	unsigned char* data = stbi_load(m_texturePath.c_str(), &m_textureWidth,
		&m_textureHeight, &m_textureFormat, STBI_default);
	assert(data != nullptr && "Unable to load the texture at that path");

	int internalFormat = 0;
	switch (m_textureFormat)
	{
	case 1:
		internalFormat = GL_RED;
		break;
	case 2:
		internalFormat = GL_RG;
		break;
	case 3:
		internalFormat = GL_RGB;
		break;
	case 4:
		internalFormat = GL_RGBA;
		break;
	default:
		assert(false && "If you hit this, STBI is doing something weird");
		break;
	}

	glGenTextures(1, &a_ID);
	glBindTexture(GL_TEXTURE_2D, a_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_textureWidth, m_textureHeight,
		0, internalFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	stbi_image_free(data);
}


