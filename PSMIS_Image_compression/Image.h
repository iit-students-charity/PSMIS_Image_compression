#pragma once

#ifndef IMAGE_H
#define IMAGE_H

#include <CImg.h>

#include "util.h"
#include "image_snippet.h"


class Image
{
private:
	uint hiddenNeuronsNumber;
	uint snippetWidth;
	uint snippetHeight;

	uint tempHeight;
	uint tempWidth;

	cimg_library::CImg<uchar>* image;
	vector<ImageSnippet*>* snippets;

	char* path;
	uint compressionIterationNumber = 0;

	void initSnippets();
public:
	Image(uint hiddenNeuronsNumber, uint snippetWidth, uint snippetHeight);
	Image(uint hiddenNeuronsNumber, uint snippetWidth, uint snippetHeight, const char* path);

	uint getN() const;
	uint getM() const;
	uint getP() const;
	uint getTempWidth() const;
	uint getTempHeight() const;
	vector<ImageSnippet*>* getSnippets() const;
	
	uint getSnippetsNumber() const;
	uint getWidth() const;
	uint getHeight() const;
	void setColor(uint x, uint y, int* color);

	void load(const char* path);
	void save();

	~Image();
};

#endif // IMAGE_H