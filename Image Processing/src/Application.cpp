#include <iostream>
#include <string>

#include "Image.h"

int main()
{
	Image img("res/test.png");
	img.Grayscale_Avg();
	img.Write("res/test1.png");

	return 0;
}