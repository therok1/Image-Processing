#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"

#include "vendor/stb_image/stb_image.h"
#include "vendor/stb_image/stb_image_write.h"

#include <iostream>

Image::Image(const std::string& filepath)
	: Data(nullptr), Size(0), Width(0), Height(0), 
	BPP(0)
{
	if (Read(filepath))
	{
		std::cout << "Read " << filepath << std::endl;
		Size = Width * Height * BPP;
	}
	else
	{
		std::cout << "Failed to read " << filepath << std::endl;
	}
}

Image::Image(int width, int height, int channels)
	: Data(nullptr), Size(0), Width(width), Height(height), 
	BPP(channels)
{
	Size = width * height * channels;
	Data = new unsigned char[Size];
}

Image::Image(const Image& image)
	: Image(image.Width, image.Height, image.BPP)
{
	std::memcpy(Data, image.Data, image.Size);
}

Image::~Image()
{
	stbi_image_free(Data);
}

bool Image::Read(const std::string& filepath)
{
	Data = stbi_load(filepath.c_str(), &Width, &Height, &BPP, 0);

	return Data != nullptr;
}

bool Image::Write(const std::string& filepath)
{
	ImageFileExtension extension = GetImageFileExtension(filepath);
	int success = 0;
	switch (extension)
	{
	case ImageFileExtension::PNG:
		success = stbi_write_png(filepath.c_str(), Width, Height, BPP, Data, Width * BPP);
		break;
	case ImageFileExtension::JPG:
		success = stbi_write_jpg(filepath.c_str(), Width, Height, BPP, Data, 100);
		break;
	case ImageFileExtension::BMP:
		success = stbi_write_bmp(filepath.c_str(), Width, Height, BPP, Data);
		break;
	case ImageFileExtension::TGA:
		success = stbi_write_tga(filepath.c_str(), Width, Height, BPP, Data);
		break;
	}

	return success != 0;
}

ImageFileExtension Image::GetImageFileExtension(const std::string& filepath)
{
	std::size_t extensionPos = filepath.rfind(".");
	if (extensionPos != std::string::npos)
	{
		std::string extension = filepath.substr(extensionPos);
		if (extension == ".png")
			return ImageFileExtension::PNG;
		else if (extension == ".jpg")
			return ImageFileExtension::JPG;
		else if (extension == ".bmp")
			return ImageFileExtension::BMP;
		else if (extension == ".tga")
			return ImageFileExtension::TGA;
	}
	return ImageFileExtension::PNG;
}

Image& Image::Grayscale_Avg()
{
	if (BPP < 3)
	{
		std::cout << "Image is assumed to already be grayscale." << std::endl;
	}
	else
	{
		for (int i = 0; i < Size; i += BPP)
		{
			int gray = (Data[i] + Data[i + 1] + Data[i + 2]) / 3;
			std::memset(Data + i, gray, 3);
		}
	}
	return *this;
}
