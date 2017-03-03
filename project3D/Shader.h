#pragma once
#include <string>


class Shader
{
public:

	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();

	Shader(const Shader& other) = delete;
	Shader(Shader&& other);
	Shader& operator=(const Shader& other) = delete;


	unsigned int GetProgramID() const { return m_programID; }




protected:

private:

	void MakeShaderProgram(std::string vertexPath, std::string fragmentPath);
	
	unsigned int MakeShader(unsigned int type, std::string path);

	unsigned int m_programID;
};