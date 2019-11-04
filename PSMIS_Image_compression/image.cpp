#include <CImg.h>

#include "Image.h"
#include "util.h"


Image::Image(uint p, uint n, uint m)
{
	this->p = p;
	this->n = n;
	this->m = m;

	image = new cimg_library::CImg<uchar>();
	path = nullptr;
	tempHeight = tempWidth = 0;
	snippets = nullptr;

	compressionIterationNumber = 0;
}

Image::Image(uint p, uint n, uint m, const char* path) : Image(p, n, m)
{
	this->path = (char*)path;
	load(path);

	tempWidth = image->width() / m;
	tempHeight = image->height() / n;
}

void Image::load(const char* path)
{
	image->load(path);
}

void Image::save()
{
	image->save(path, ++compressionIterationNumber, 1);
}

void Image::initSnippets()
{
	snippets = new ImageSnippet[tempWidth * tempHeight];
	int x = 0;
	int y = 0;

	for (int w = 0; w < tempWidth; w++)
	{
		for (int h = 0; h < tempHeight; h++)
		{
			ImageSnippet snippet(x, y, n, m);

			for (int widthIndex = 0; widthIndex < m; widthIndex++)
			{
				for (int heightIndex = 0; heightIndex < n; heightIndex++)
				{
					if (widthIndex < image->width() && heightIndex < image->height())
					{
						int currX = widthIndex + x;
						int currY = heightIndex + y;
						snippet.addPixel(
							(*image)(currX, currY, 0, 0),
							(*image)(currX, currY, 0, 1),
							(*image)(currX, currY, 0, 2)
						);
					}
					else
					{
						snippet.addPixel(-1., -1., -1.);
					}
				}
			}
			y += n;

			snippet.createX0();
			snippets[w * 10 + h] = snippet;
		}
		x += m;
	}
}

Image::~Image()
{
	delete image;
	delete[] snippets;

	delete[] path;
}