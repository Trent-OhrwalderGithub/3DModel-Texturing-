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

protected:


private:

	void LoadTexture();

	unsigned int m_textureID;
	int m_textureWidth;
	int m_textureHeight;
	int m_textureFormat;

	std::string m_texturePath;
};