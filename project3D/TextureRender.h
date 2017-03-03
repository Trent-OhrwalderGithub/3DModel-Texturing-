#pragma once

#include <string>


class TextureRender
{
public:

	TextureRender(std::string filePath);
	~TextureRender();

	TextureRender(const TextureRender& other) = delete;
	TextureRender(TextureRender&& other);

	unsigned int GetTextureID() const { return m_textureID; }
	unsigned int GetNormalID() const { return m_normalMap; }
	unsigned int GetSpecularMapID() const { return m_specularMap; }

protected:


private:

	void LoadTexture(unsigned int& a_ID);

	unsigned int m_textureID, m_normalMap, m_specularMap;
	int m_textureWidth;
	int m_textureHeight;
	int m_textureFormat;

	std::string m_texturePath;
};