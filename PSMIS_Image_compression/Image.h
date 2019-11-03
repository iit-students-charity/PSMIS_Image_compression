#pragma once

#include <CImg.h>

#include "util.h"
#include "rectangle.h"


class Image
{
private:
	uint p;
	uint n;
	uint m;

	uint tempHeight;
	uint tempWidth;

	cimg_library::CImg<uchar> image;
	ImageSnippet* snippets;
public:
	void initSnippets();
};