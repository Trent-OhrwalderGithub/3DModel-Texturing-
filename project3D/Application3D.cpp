#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "RenderData.h"
#include "Shader.h"
#include "GeometryHelper.h"

#include <gl_core_4_4.h>
#include "RenderModel.h"
#include "TextureRender.h"
#include "FlyCam.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Application3D::Application3D() {

}

Application3D::~Application3D() {

}

bool Application3D::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	//m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
	//									  getWindowWidth() / (float)getWindowHeight(),
	//									  0.1f, 1000.f);

	// Moving Cam.

	m_cam = new FlyCam(m_window, 5.0f); // Speed.
	m_cam->setPerspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(),
		0.1f, 1000.f);

	m_cam->lookAt(glm::vec3(10, 10, 10),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));

	m_gridRenderData = GeometryHelper::CreateGrid(10, 10, 10, 10, glm::vec4(1, 0, 0, 1));
	m_gridShader = new Shader("./shaders/grid.vert", "./shaders/grid.frag");

	//m_starDestroyer = RenderModel::LoadOBJFromDisk("./models/starwars/star-destroyer.obj");
	//m_starDestroyerShader = new Shader("./shaders/objRender.vert", "./shaders/objRender.frag");

	//m_darthVader = RenderModel::LoadOBJFromDisk("./models/starwars/darth-vader.obj");
	//m_DarthVaderShader = new Shader("./shaders/objRender.vert", "./shaders/objRender.frag");
	//
	m_StormTrooper = RenderModel::LoadOBJFromDisk("./models/starwars/Stormtrooper.obj");
	m_StormTrooperShader = new Shader("./shaders/TextureRender.vert", "./shaders/TextureRender.frag");
	m_StormTrooperDiffuse = new TextureRender("./models/StormTrooperTexture/Stormtrooper_D.tga");
	m_StormTrooperNormal = new TextureRender("./models/StormTrooperTexture/Stormtrooper_N.tga");
	m_StormTrooperSpecular = new TextureRender("./models/StormTrooperTexture/Stormtrooper_S.tga");
	//
	//m_TIE_Fighter = RenderModel::LoadOBJFromDisk("./models/starwars/TIE-fighter.obj");
	//m_Tie_FighterShader = new Shader("./shaders/objRender.vert", "./shaders/objRender.frag");

	return true;
}

void Application3D::shutdown() {

	for (auto& renderData : m_starDestroyer)
	{
		delete renderData;
	}
	delete m_StormTrooperDiffuse;
	delete m_gridRenderData;
	delete m_gridShader;

	Gizmos::destroy();
}

void Application3D::update(float deltaTime) {

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Draws in wire form.

	// query time since application started
	float time = getTime();

	// rotate camera
	m_viewMatrix = glm::lookAt(vec3(glm::sin(time) * 10, 10, glm::cos(time) * 10),
							   vec3(0), vec3(0, 1, 0));

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	//Gizmos::addTransform(mat4(1));

	// demonstrate a few shapes
	//Gizmos::addAABBFilled(vec3(0), vec3(1), vec4(0, 0.5f, 1, 0.25f));
	//Gizmos::addSphere(vec3(5, 0, 5), 1, 8, 8, vec4(1, 0, 0, 0.5f));
	//Gizmos::addRing(vec3(5, 0, -5), 1, 1.5f, 8, vec4(0, 1, 0, 1));
	//Gizmos::addDisk(vec3(-5, 0, 5), 1, 16, vec4(1, 1, 0, 1));
	//Gizmos::addArc(vec3(-5, 0, -5), 0, 2, 1, 8, vec4(1, 0, 1, 1));
	//
	//mat4 t = glm::rotate(time, glm::normalize(vec3(1, 1, 1)));
	//t[3] = vec4(-2, 0, 0, 1);
	//Gizmos::addCylinderFilled(vec3(0), 0.5f, 1, 5, vec4(0, 1, 1, 1), &t);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_cam->Update(deltaTime);
}

void Application3D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective in case window resized
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
										  getWindowWidth() / (float)getWindowHeight(),
										  0.1f, 1000.f);

	Gizmos::draw(m_cam->getProjectionView());

	//glUseProgram(m_program);
	//
	//glUseProgram(m_gridShader->GetProgramID());
	//int locCam = glGetUniformLocation(m_gridShader->GetProgramID(), "projectionViewWorldMatrix");
	//glUniformMatrix4fv(locCam, 1, GL_FALSE, &(m_cam->getProjectionView()[0][0]));
	
	glm::mat4 projView = m_projectionMatrix * m_viewMatrix;
	
	glUseProgram(m_gridShader->GetProgramID());
	
	int loc = glGetUniformLocation(m_gridShader->GetProgramID(), "projectionViewMatrix");
	assert(loc != -1);
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(projView));
	
	glm::mat4 modelMatrix(1);
	loc = glGetUniformLocation(m_gridShader->GetProgramID(), "modelMatrix");
	assert(loc != -1);
	 glUniformMatrix4fv(loc, 1, false, glm::value_ptr(modelMatrix));

	//m_gridRenderData->Render();


	// Star Destroyer
	//glUseProgram(m_starDestroyerShader->GetProgramID());
	//loc = glGetUniformLocation(m_starDestroyerShader->GetProgramID(), "projectViewMatrix");
	//assert(loc != -1);
	//glUniformMatrix4fv(loc, 1, false, glm::value_ptr(m_cam->getProjectionView()));
	//
	//
	//modelMatrix = glm::mat4(1);
	//modelMatrix[3].x = 0;
	//loc = glGetUniformLocation(m_starDestroyerShader->GetProgramID(), "modelMatrix");
	//assert(loc != -1);
	//glUniformMatrix4fv(loc, 1, false, glm::value_ptr(modelMatrix));
	//
	//for (auto& renderData : m_starDestroyer)
	//{
	//	renderData->Render();
	//}

	// Darth Vader
	//glUseProgram(m_DarthVaderShader->GetProgramID());
	//loc = glGetUniformLocation(m_DarthVaderShader->GetProgramID(), "projectViewMatrix");
	//assert(loc != -1);
	//glUniformMatrix4fv(loc, 1, false, glm::value_ptr(m_cam->getProjectionView()));
	//
	//
	//modelMatrix = glm::mat4(1);
	//modelMatrix[3].x = -10;
	//loc = glGetUniformLocation(m_DarthVaderShader->GetProgramID(), "modelMatrix");
	//assert(loc != -1);
	//glUniformMatrix4fv(loc, 1, false, glm::value_ptr(modelMatrix));
	//
	//for (auto& renderData : m_darthVader)
	//{
	//	renderData->Render();
	//}

	// Stormtrooper
	glUseProgram(m_StormTrooperShader->GetProgramID());
	loc = glGetUniformLocation(m_StormTrooperShader->GetProgramID(), "MVP");
	assert(loc != -1);
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(m_cam->getProjectionView()));

	
	//modelMatrix = glm::mat4(1);
	//modelMatrix[3].x = 0 /*15*/;
	//loc = glGetUniformLocation(m_StormTrooperShader->GetProgramID(), "modelMatrix");
	//assert(loc != -1);
	//glUniformMatrix4fv(loc, 1, false, glm::value_ptr(modelMatrix));
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_StormTrooperDiffuse->GetTextureID());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_StormTrooperNormal->GetNormalID());

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_StormTrooperSpecular->GetSpecularMapID());

	loc = glGetUniformLocation(m_StormTrooperShader->GetProgramID(), "myTextureSampler");
	assert(loc != -1);
	glUniform1i(loc, 0); // Change between, 0-2 to load different maps. (Diffuse, Normal & Specular.

	for (auto& renderData : m_StormTrooper)
	{
		renderData->Render();
	}

	// TIE fighter
	//glUseProgram(m_Tie_FighterShader->GetProgramID());
	//loc = glGetUniformLocation(m_Tie_FighterShader->GetProgramID(), "projectViewMatrix");
	//assert(loc != -1);
	//glUniformMatrix4fv(loc, 1, false, glm::value_ptr(m_cam->getProjectionView()));
	//
	//
	//modelMatrix = glm::mat4(1);
	//modelMatrix[3].x = -20;
	//loc = glGetUniformLocation(m_Tie_FighterShader->GetProgramID(), "modelMatrix");
	//assert(loc != -1);
	//glUniformMatrix4fv(loc, 1, false, glm::value_ptr(modelMatrix));
	//
	//for (auto& renderData : m_TIE_Fighter)
	//{
	//	renderData->Render();
	//}

	//Gizmos::draw(m_projectionMatrix * m_viewMatrix); // Draws shapes
}