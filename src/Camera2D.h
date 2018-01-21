/*
 * Camera2D.h
 *
 *  Created on: Jul 16, 2015
 *      Author: Robert
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SnowEngine
{

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void init(int screenWidth, int screenHeight);
	void update();

	void setPosition(const glm::vec2& position);
	glm::vec2 getPosition();
	void setScale(float scale);
	float getScale();
	glm::mat4 getCameraMatrix();
	void convertScreenToWorldCoords(glm::vec2& screen);
	bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);
private:
	int m_screenWidth, m_screenHeight;
	glm::vec2 m_position;
	glm::mat4 m_cameraMatrix;
	glm::mat4 m_orthoMatrix;
	float m_scale;
	bool m_needsMatrixUpdate;
};

} /* namespace SnowEngine */
