#include "FlyCam.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>



FlyCam::FlyCam(GLFWwindow* window, float speed)
	: m_speed(speed)
	, m_rotate(glm::pi<float>() * 0.05f)
	, m_window(window)
{

}

void FlyCam::mouseInput(double dt)
{
	glm::vec3 position = glm::vec3(0, 0, 5);
	float horizontalAngle = glm::pi<float>() * 0.25f;
	float verticleAngle = 0.0f;
	float mouseSpeed = 0.005f;

	double xPos, yPos;

	int windowWidth, windowHeight; 
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	glfwGetCursorPos(m_window, &xPos, &yPos);
	glfwSetCursorPos(m_window, windowWidth / 2, windowHeight / 2);

	float xOffset = windowWidth / 2 - xPos;
	float yOffset = windowHeight / 2 - yPos;

	horizontalAngle += mouseSpeed * dt * xOffset;
	verticleAngle += mouseSpeed * dt * yOffset;


	if (xOffset > 0) 
		int i = 0;
	glm::vec3 direction(
		cos(verticleAngle) * sin(horizontalAngle),
		sin(verticleAngle),
		cos(verticleAngle) * cos(horizontalAngle)
	);

	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - glm::pi<float>() * 0.25f / 2.0f),
		0,
		cos(horizontalAngle - glm::pi<float>() * 0.25f / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);


	getDirectionRotation(dt, xOffset, yOffset);
	/*if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{

		if (m_bViewButtonClicked == false)
		{
			int width, height;
			glfwGetFramebufferSize(m_window, &width, &height);
			m_cursorX = width / 2.0f;
			m_cursorY = height / 2.0f;
			glfwSetCursorPos(m_window, width / 2, height / 2);

			m_bViewButtonClicked = true;
		}
		else
		{
			double mouseX, mouseY;
			glfwGetCursorPos(m_window, &mouseX, &mouseY);

			double xOffSet = mouseX - m_cursorX;
			double yOffSet = mouseY - m_cursorY;

			getDirectionRotation(dt, xOffSet, yOffSet);
		}

		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		glfwSetCursorPos(m_window, width / 2, height / 2);

	}
	else
	{
		m_bViewButtonClicked = false;
	}*/


	/*glm::vec3 faceChange(0.0f);

	if (glfwGetKey(m_window, GLFW_KEY_UP))
	{
		faceChange.y -= 1.5f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_DOWN))
	{
		faceChange.y += 1.5f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT))
	{
		faceChange.x -= 1.5f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT))
	{
		faceChange.x += 1.5f;
	}
	*/


}

void FlyCam::getDirectionRotation(double dt, double xPos, double yPos)
{
	if (yPos != 0.0f)
	{
		glm::mat4 rot = glm::rotate((float)(m_rotate * dt * yPos), glm::vec3(1, 0, 0));
		setTransform(getTransform()*rot);
	}

	if (xPos != 0.0f)
	{
		glm::mat4 rot = glm::rotate((float)(m_rotate * dt * xPos), glm::vec3(0, 1, 0));
		setTransform(getTransform()*rot);
	}

	glm::mat4 oldTrans = getTransform(); // old transformation
		
	glm::mat4 trans;					 // new transformation
		
	glm::vec3 worldUp = glm::vec3(0, 1, 0);

	// Otho normalization (Hiding problem not fixing)

	//Right
	glm::vec3 oldForward = glm::vec3(oldTrans[2].x, oldTrans[2].y, oldTrans[2].z);

	trans[0] = glm::normalize(glm::vec4(glm::cross(worldUp, oldForward), 0));
	//Up
	glm::vec3 newRight = glm::vec3(trans[0].x, trans[0].y, trans[0].z);
	trans[1] = glm::normalize(glm::vec4(glm::cross(oldForward, newRight), 0));
	//Forward
	trans[2] = glm::normalize(oldTrans[2]);

	//Position
	trans[3] = oldTrans[3];

	setTransform(trans);
}

void FlyCam::Update(float deltaTime)
{

	glm::mat4 transform		= getTransform();
	glm::vec4 vRight		= transform[0];
	glm::vec4 vUp			= transform[1];
	glm::vec4 vForward		= transform[2];

	glm::vec4 moveDirection;

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		moveDirection -= (vForward * m_speed);
	}

	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		moveDirection += (vForward * m_speed);
	}

	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		moveDirection -= (vRight * m_speed);
	}

	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		moveDirection += (vRight * m_speed);
	}

	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		moveDirection += (vUp * m_speed);
	}

	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		moveDirection -= (vUp * m_speed);
	}

	if (glm::length(moveDirection) > 0.0f)
	{
		transform[3] += moveDirection * deltaTime;
		setTransform(transform);
	}
	
	mouseInput(deltaTime);
}


