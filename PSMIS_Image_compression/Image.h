#pragma once

#ifndef IMAGE_H
#define IMAGE_H

#include <CImg.h>

#include "util.h"
#include "image_snippet.h"


class Image
{
private:
	uint snippetWidth;
	uint snippetHeight;

	uint tempHeight;
	uint tempWidth;

	cimg_library::CImg<uchar>* image;
	vector<ImageSnippet*>* snippets;

	char* rawPath;
	uint compressionIterationNumber = 0;

	void initSnippets();
public:
	Image(uint snippetWidth, uint snippetHeight);
	Image(uint snippetWidth, uint snippetHeight, const char* path);

	uint getN() const;
	uint getM() const;
	uint getSnippetsHorizontalCapacity() const;
	uint getSnippetsVerticalCapacity() const;
	vector<ImageSnippet*>* getSnippets() const;
	
	uint getSnippetsNumber() const;
	uint getWidth() const;
	uint getHeight() const;
	void setColor(uint x, uint y, int* color);

	cimg_library::CImg<uchar>* getRaw();
	void update(const char* path);
	void load(const char* path);
	void save();

	~Image();
};

#endif // IMAGE_H