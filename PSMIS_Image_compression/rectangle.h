#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "util.h"
#include "matrix.h"

class Rectangle 
{
private:	
	uint width;
	uint height;

	uint startX;
	uint startY;
public:
	Rectangle(uint startX = 0U, uint startY = 0U, uint width = 0U, uint height = 0U);

	uint getWidth() const;
	uint getHeight() const;

	uint getStartX() const;
	uint getStartY() const;
};

class ImageSnippet : Rectangle 
{
private:
	Matrix* pixels;
public:
	ImageSnippet(uint startX, uint startY, uint width, uint height);

	~ImageSnippet();
};

#endif // RECTANGLE_H