#include "Shader.h"
#include <gl_core_4_4.h>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>


Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	MakeShaderProgram(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	if (m_programID != -1)
	{
		glDeleteProgram(m_programID);
	}
}

Shader::Shader(Shader && other)
{
	m_programID = other.m_programID;
	other.m_programID = -1;
}

void Shader::MakeShaderProgram(std::string vertexPath, std::string fragmentPath)
{
	unsigned int vertexShader = MakeShader(GL_VERTEX_SHADER, vertexPath);
	unsigned int fragmentShader = MakeShader(GL_FRAGMENT_SHADER, fragmentPath);

	assert(vertexShader != -1 && fragmentShader != -1);

	// Create Shader Program, attached the required shaders.
	// and then attempt to link shaders together.
	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	int success = 0;

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);

	if (success == GL_FALSE)
	{
		int infoLogLength;
		
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		std::cout << "Error trying to link shaders (" << vertexPath << ", " << fragmentPath << "): /n";

		std::cout << infoLog << '\n';

		assert(false && "Shader failed to compile correctly.");
		
		delete[] infoLog;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

unsigned int Shader::MakeShader(unsigned int type, std::string path)
{
	std::ifstream file; // Creating a new file
	file.open(path.c_str(), std::ifstream::in); // Inporting object
	if (!file.good()) // Check to see if worked
	{
		return -1;
	}

	// Read the data in the file into a temp stream and then close the file.
	std::stringstream ss; // If successful.
	ss << file.rdbuf(); // Read from file buffer and move to the 'SS'.
	file.close(); // Closing file

	std::string codeString = ss.str(); // Setting 'codeString' to 'ss'

	// Create and comppile the shader.
	unsigned int shaderHandler = glCreateShader(type);

	const char* shaderCode = codeString.c_str();

	glShaderSource(shaderHandler, 1, (const char**)&shaderCode, 0);
	glCompileShader(shaderHandler);

	// Return the compiled shader to be used in a shader program.
	return shaderHandler;
}



