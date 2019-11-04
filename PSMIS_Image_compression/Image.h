#pragma once

#ifndef IMAGE_H
#define IMAGE_H

#include <CImg.h>

#include "util.h"
#include "image_snippet.h"


class Image
{
private:
	uint p;
	uint n;
	uint m;

	uint tempHeight;
	uint tempWidth;

	cimg_library::CImg<uchar>* image;
	ImageSnippet* snippets;

	char* path;
	uint compressionIterationNumber = 0;
public:
	Image(uint p, uint n, uint m);
	Image(uint p, uint n, uint m, const char* path);

	uint getN() const;
	uint getM() const;
	uint getP() const;
	uint getTempWidth() const;
	uint getTempHeight() const;
	ImageSnippet* getSnippets() const;
	
	uint getSnippetsNumber() const;
	uint getWidth() const;
	uint getHeight() const;
	void setColor(uint x, uint y, int* color);

	void load(const char* path);
	void save();

	void initSnippets();

	~Image();
};

#endif // IMAGE_H