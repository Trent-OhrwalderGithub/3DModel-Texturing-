#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>

#include "RenderModel.h"

class RenderData;
class Shader;
class Camera;
class TextureRender;

class Application3D : public aie::Application {
public:

	Application3D();
	virtual ~Application3D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	std::vector<OpenGLInfo> m_glInfo;

protected:

	using OBJMesh = std::vector<RenderData*>;

	RenderData* m_gridRenderData;
	Shader*		m_gridShader;

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	//unsigned int m_program;
	Camera* m_cam;

	Shader* m_starDestroyerShader;
	OBJMesh m_starDestroyer;

	Shader* m_DarthVaderShader;
	OBJMesh m_darthVader;

	Shader* m_StormTrooperShader;
	OBJMesh m_StormTrooper;
	TextureRender* m_StormTrooperDiffuse;

	Shader* m_Tie_FighterShader;
	OBJMesh m_TIE_Fighter;

	

};