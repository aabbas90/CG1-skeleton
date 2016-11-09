#include "ImageDrawing.h"

using namespace rt;

void DrawImage::displayImage(Image image)
{
	// img (Image width, Image height, Image depth, Number of channels, initialization value)
	cimg_library::CImg<float> img(image.width(), image.height(), 1, 3, 0);
	for (uint i = 0; i < image.width(); i++)
	{
		for (uint j = 0; j < image.height(); j++)
		{
			RGBColor value = image(i, j);

			img(i, j, 0) = value.r;
			img(i, j, 1) = value.g;
			img(i, j, 2) = value.b;
		}
	}
	cimg_library::CImgDisplay disp;
	disp.display(img);
	getchar();
}
