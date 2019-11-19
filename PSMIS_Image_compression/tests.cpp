#include "tests.h"
#include "util.h"

#include <iostream>
#include "Image.h"
#include "neural_network.h"

const char** paths = new const char* [5]
{
	"C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\redhead.png",
	"C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\flower.png",
	"C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\fight.png",
	"C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\bread.png",
	"C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\smousy.png"
};

uint n;
uint m;
uint p;
double e;

void run_IOnDiffImages()
{
	n = 2;
	m = 2;
	p = n * m;
	e = 10777.;

	Image* image = new Image(n, m);

	NeuralNetwork* nn = new NeuralNetwork(image, e, p);

	//image->update(paths[0]);
	//image->update(paths[1]);
	image->update(paths[2]);
	//image->update(paths[3]);
	//image->update(paths[4]);

	nn->run();
}

void run_IOnZ()
{

}

void run_IOnE()
{

}

void run_IOnAlpha()
{

}