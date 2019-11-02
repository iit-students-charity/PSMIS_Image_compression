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
	pixels = new Matrix(height, width);
}

ImageSnippet::~ImageSnippet()
{
	delete pixels;
}