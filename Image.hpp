#pragma once
#include <string>

	struct Image
	{
		Image(const std::string& path, bool flip = true);
		~Image();

		unsigned char* buffer;
		int width;
		int height;
	};
