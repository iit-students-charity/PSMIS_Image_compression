#include <vector>
#include <CImg.h>

#include "image_snippet.h"


ImageSnippet::ImageSnippet(uint startX, uint startY, uint width, uint height)
	: width(width), height(height), startX(startX), startY(startY)
{
	x0 = nullptr;
}

uint ImageSnippet::getWidth() const
{
	return width;
}

uint ImageSnippet::getHeight() const
{
	return height;
}

uint ImageSnippet::getStartX() const
{
	return startX;
}

uint ImageSnippet::getStartY() const
{
	return startY;
}

Matrix* ImageSnippet::getX0() const
{
	return x0;
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

void ImageSnippet::createX0()
{
	uint numberOfRows = 1;
 	uint numberOfColumns = pixels.size();

	double** valuesVector = new double*[numberOfRows];
	valuesVector[0] = new double[numberOfColumns];
	for (int pixelIndex = 0; pixelIndex < numberOfColumns; pixelIndex++) {
		valuesVector[0][pixelIndex] = pixels.at(pixelIndex);
	}

	if (x0 != nullptr) delete x0;
	x0 = new Matrix(valuesVector, numberOfRows, numberOfColumns);
}

ImageSnippet::~ImageSnippet()
{
	delete x0;
}