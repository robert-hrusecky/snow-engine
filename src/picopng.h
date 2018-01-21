/*
 * picopng.h
 *
 *  Created on: Jul 13, 2015
 *      Author: Robert
 */

#pragma once

#include <vector>
#include <cstdlib>

namespace SnowEngine
{

extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);

}
