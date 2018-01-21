/*
 * SpriteSheet.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: Robert
 */

#include "SpriteSheet.h"

#include <cstdlib>
#include <fstream>
#include <glm/glm.hpp>

namespace SnowEngine
{

SpriteSheet::SpriteSheet()
{
	// TODO Auto-generated constructor stub

}

void SpriteSheet::init(const std::string& filePath, const GLTexture& texture)
{
	std::ifstream in;
	in.open(filePath);
	if(in.fail())
	{
		perror(filePath.c_str());
	}
	int count;
	in >> count;
	for (int i = 0; i < count; i++)
	{
		glm::ivec4 rect;
		int num, xNum, fps;
		in >> rect.x;
		in >> rect.y;
		in >> rect.z;
		in >> rect.w;
		in >> num;
		in >> xNum;
		in >> fps;
		m_anims.emplace_back(rect, num, xNum, fps, texture);
	}
	in.close();
}

SpriteAnimation SpriteSheet::getAnimation(int index)
{
	return m_anims[index];
}

} /* namespace SnowEngine */
