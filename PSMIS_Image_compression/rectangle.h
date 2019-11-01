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
	Rectangle(uint startX = 0, uint startY = 0, uint width = 0, uint height = 0);

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
	ImageSnippet(uint startX, uint startY, uint width, uint height) 
		: Rectangle(startX, startY, width, height) 
	{
		pixels = new Matrix(height, width);
	}

	~ImageSnippet()
	{
		delete pixels;
	}
};

#endif // RECTANGLE_H