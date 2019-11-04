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

	uint tempHeight = 1;
	uint tempWidth = 1;

	cimg_library::CImg<uchar>* image;
	ImageSnippet* snippets;

	const char* path = "\\src\\1.png";
	uint compressionIterationNumber = 0;
public:
	Image();

	void load(const char* path);
	void save();

	void initSnippets();

	~Image();
};

#endif // IMAGE_H