#define cimg_use_png
#include <CImg.h>

#include "Image.h"
#include "util.h"


Image::Image(uint n, uint m)
{
	this->snippetWidth = n;
	this->snippetHeight = m;

	image = new cimg_library::CImg<uchar>();
	path = nullptr;
	tempHeight = tempWidth = 0;
	snippets = nullptr;

	compressionIterationNumber = 0;
}

Image::Image(uint n, uint m, const char* path) : Image(n, m)
{
	this->path = (char*)path;
	load(path);
	tempWidth = image->width() / m;
	tempHeight = image->height() / n;
	
	initSnippets();
}

uint Image::getN() const
{
	return snippetWidth;
}

uint Image::getM() const
{
	return snippetHeight;
}

uint Image::getTempWidth() const
{
	return tempWidth;
}

uint Image::getTempHeight() const
{
	return tempHeight;
}

vector<ImageSnippet*>* Image::getSnippets() const
{
	return snippets;
}

uint Image::getSnippetsNumber() const
{
	return tempHeight * tempWidth;
}

uint Image::getWidth() const
{
	return image->width();
}

uint Image::getHeight() const
{
	return image->height();
}

void Image::setColor(uint x, uint y, int* color)
{
	(*image)(x, y, 0) = color[0];
	(*image)(x, y, 1) = color[1];
	(*image)(x, y, 2) = color[2];
}

void Image::load(const char* path)
{
	image->load(path);
}

void Image::save()
{
	image->save(path, 1, 1);
}

void Image::initSnippets()
{
	snippets = new vector<ImageSnippet*>();
	int x = 0;
	int y = 0;

	for (int w = 0; w < tempWidth; w++)
	{
		y = 0;

		for (int h = 0; h < tempHeight; h++)
		{
			ImageSnippet* snippet = new ImageSnippet(x, y, snippetWidth, snippetHeight);

			for (int widthIndex = 0; widthIndex < snippetHeight; widthIndex++)
			{
				for (int heightIndex = 0; heightIndex < snippetWidth; heightIndex++)
				{
					if (widthIndex < image->width() && heightIndex < image->height())
					{
						int currX = widthIndex + x;
						int currY = heightIndex + y;
						snippet->addPixel(
							snippet->transformColor((*image)(currX, currY, 0, 0)),
							snippet->transformColor((*image)(currX, currY, 0, 1)),
							snippet->transformColor((*image)(currX, currY, 0, 2))
						);
					}
					else
					{
						snippet->addPixel(-1., -1., -1.);
					}
				}
			}
			y += snippetWidth;

			snippet->createX0();
			snippets->push_back(snippet);
		}
		x += snippetHeight;
	}
}

Image::~Image()
{
	delete image;
	delete[] snippets;

	delete[] path;
}