#pragma once

#ifndef IMAGE_SNIPPET_H
#define IMAGE_SNIPPET_H

#include <vector>
#include <CImg.h>

#include "util.h"
#include "matrix.h"


class ImageSnippet
{
private:
	uint width;
	uint height;

	uint startX;
	uint startY;

	vector<double> pixels;
	Matrix* x0;
public:
	ImageSnippet(
		uint startX = 0U, uint startY = 0U, 
		uint width = 0U, uint height = 0U
	);

	uint getWidth() const;
	uint getHeight() const;

	uint getStartX() const;
	uint getStartY() const;

	Matrix* getX0() const;
	
	int restoreColor(double color);
	double transformColor(double color);

	void addPixel(double red, double green, double blue);

	void createX0();

	~ImageSnippet();
};

#endif // IMAGE_SNIPPET_H