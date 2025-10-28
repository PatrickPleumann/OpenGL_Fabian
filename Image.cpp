#include "Image.hpp"
#include "stb_image.h"

Image::Image(const std::string& path, bool flip)
{
	{
		int bitsPerPixel;

		stbi_set_flip_vertically_on_load(flip);
		buffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);
	}
}

Image::~Image()
{
	stbi_image_free(buffer);
}
