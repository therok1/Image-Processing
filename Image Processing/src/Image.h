#pragma once

#include <string>
#include <cstdint>

enum class ImageFileExtension
{
	PNG,
	JPG,
	BMP,
	TGA
};

struct Image
{
	uint8_t* Data;
	std::size_t Size;
	int Width, Height, BPP;

	Image(const std::string& filepath);
	Image(int width, int height, int channels);
	Image(const Image& image);
	~Image();

	bool Read(const std::string& filepath);
	bool Write(const std::string& filepath);

	ImageFileExtension GetImageFileExtension(const std::string& filepath);

	Image& Grayscale_Avg();
};

