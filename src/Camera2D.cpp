/*
 * Camera2D.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: Robert
 */

#include "Camera2D.h"

namespace SnowEngine
{

Camera2D::Camera2D() :
		m_screenWidth(500), m_screenHeight(500), m_position(0.0f, 0.0f), m_cameraMatrix(1.0f), m_orthoMatrix(1.0f), m_scale(1.0f), m_needsMatrixUpdate(true)
{
}

Camera2D::~Camera2D()
{
	// TODO Auto-generated destructor stub
}

void Camera2D::init(int screenWidth, int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_orthoMatrix = glm::ortho(-screenWidth / 2.0f,  screenWidth / 2.0f, -screenHeight / 2.0f, screenHeight / 2.0f);
}

void Camera2D::update()
{
	if (m_needsMatrixUpdate)
	{
		glm::vec3 scale(m_scale, m_scale, 0.0f);
		m_cameraMatrix = glm::scale(m_orthoMatrix, scale);
		glm::vec3 translate(-m_position.x, -m_position.y, 0.0f);
		m_cameraMatrix = glm::translate(m_cameraMatrix, translate);
		m_needsMatrixUpdate = false;
	}
}

void Camera2D::setPosition(const glm::vec2& position)
{
	m_position = position;
	m_needsMatrixUpdate = true;
}

glm::vec2 Camera2D::getPosition()
{
	return m_position;
}

void Camera2D::setScale(float scale)
{
	m_scale = scale;
	m_needsMatrixUpdate = true;
}

float Camera2D::getScale()
{
	return m_scale;
}

glm::mat4 Camera2D::getCameraMatrix()
{
	return m_cameraMatrix;
}

void Camera2D::convertScreenToWorldCoords(glm::vec2& screen)
{
	screen -= glm::vec2(m_screenWidth / 2.0f, m_screenHeight / 2.0f);
	screen.y = -screen.y;
	screen /= m_scale;
	screen += m_position;
}

// hd + hsd - abs(pos + hd - cp)

bool Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2& dimensions)
{
	glm::vec2 halfDim = dimensions / 2.0f;
	glm::vec2 depth = halfDim + glm::vec2(m_screenWidth, m_screenHeight) / (m_scale * 2.0f) - glm::abs(position + halfDim - m_position);
	return depth.x > 0 && depth.y > 0;
}

} /* namespace SnowEngine */
