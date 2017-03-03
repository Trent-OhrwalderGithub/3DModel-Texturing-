#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include "Camera.h"

struct GLFWwindow;

class FlyCam : public Camera
{
public:

	FlyCam(GLFWwindow* window, float speed);

	float getSpeed() const { return m_speed; }
	FlyCam() = default;

	void Update(float deltaTime) override;

protected:
	void mouseInput(double dt);
	void getDirectionRotation(double dt, double xPos, double yPos);

	double m_cursorX, m_cursorY;

private:
	
	float m_speed;
	float m_rotate;

	//bool m_bViewButtonClicked;

	GLFWwindow* m_window;
};