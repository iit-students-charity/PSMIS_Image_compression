#include <CImg.h>

#include "Image.h"
#include "util.h"
#include "rectangle.h"


void Image::initSnippets() {
	uint x = 0;
	snippets = new ImageSnippet[tempWidth * tempHeight];

	for (int i = 0; i < tempWidth; i++)
	{
		uint y = 0;
		for (int j = 0; j < tempHeight; j++)
		{
			ImageSnippet snippet(x, y);

			for (int widthIndex = 0; widthIndex < m; widthIndex++)
			{
				for (int heightIndex = 0; heightIndex < n; heightIndex++)
				{
					if (widthIndex < image.width() && heightIndex < image.height())
					{
						uint x = widthIndex + x;
						uint y = heightIndex + y;
						snippet.addPixel(image(x, y, 0, 0), image(x, y, 0, 1), image(x, y, 0, 2));
					}
					else
					{
						snippet.add();
						snippet.add();
						snippet.add();
					}
				}
			}
			y += n;

			snippet.createX0();
			snippets[i * 10 + j] = snippet;
		}
		x += m;
	}
}