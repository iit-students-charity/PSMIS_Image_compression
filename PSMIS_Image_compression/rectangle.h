#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include <CImg.h>

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
	//double* pixels;
	vector<double> pixels;
	Matrix* x0;
public:
	ImageSnippet(uint startX, uint startY, uint width, uint height);
	
	int restoreColor(double color);
	double transformColor(double color);

	void addPixel(double red, double green, double blue);
	void add();

	void createX0();

	~ImageSnippet();
};

#endif // RECTANGLE_H