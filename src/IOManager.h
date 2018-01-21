/*
 * IOManager.h
 *
 *  Created on: Jul 13, 2015
 *      Author: Robert
 */

#pragma once

#include <vector>
#include <string>

namespace SnowEngine
{

class IOManager
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	static bool readFileToBuffer(std::string filePath, std::string& buffer);
};

}
