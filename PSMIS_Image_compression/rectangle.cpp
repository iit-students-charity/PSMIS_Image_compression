#include <vector>
#include <CImg.h>

#include "rectangle.h"


Rectangle::Rectangle(uint startX = 0U, uint startY = 0U, uint width = 0U, uint height = 0U)
	: width(width), height(height), startX(startX), startY(startY)
{ }

uint Rectangle::getWidth() const
{
	return width;
}

uint Rectangle::getHeight() const
{
	return height;
}

uint Rectangle::getStartX() const
{
	return startX;
}

uint Rectangle::getStartY() const
{
	return startY;
}



ImageSnippet::ImageSnippet(uint startX, uint startY, uint width, uint height)
	: Rectangle(startX, startY, width, height)
{
	x0 = new Matrix(height, width);
}

ImageSnippet::~ImageSnippet()
{
	/*delete [] pixels;
	delete pixels;*/

	delete x0;
}

int ImageSnippet::restoreColor(double color) {
	double newColor = 255 * (color + 1) / 2;
	newColor = newColor < 0 ? 0 : (newColor > 255 ? 255 : newColor);
	return (int)newColor;
}

double ImageSnippet::transformColor(double color)
{
	return 2 * color / 255 - 1;
}

void ImageSnippet::addPixel(double red, double green, double blue)
{
	pixels.push_back(red);
	pixels.push_back(green);
	pixels.push_back(blue);
}

void ImageSnippet::add()
{
	pixels.push_back(-1.0);
}

void ImageSnippet::createX0()
{
	uint numberOfRows = 1;
	uint numberOfColumns = pixels.size();

	double** valuesVector = new double*[numberOfRows];
	valuesVector[0] = new double[numberOfColumns];
	for (int pixelIndex = 0; pixelIndex < numberOfColumns; pixelIndex++) {
		valuesVector[0][pixelIndex] = pixels.at(pixelIndex);
	}

	delete x0;
	x0 = new Matrix(valuesVector, numberOfRows, numberOfColumns);
}