#include <iostream>

#include "util.h"
#include "Image.h"
#include "neural_network.h"
#include "tests.h"


int main()
{
	const char* rawImagePath = nullptr;

	uint choise;
	do
	{
		std::cout << "choose an image: \n1. redhead\n2. flower\n3. fight\n4. bread\n5. witch\n";
		std::cin >> choise;

		switch (choise)
		{
		case 1:
		{
			rawImagePath = "C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\redhead.png";
			break;
		}
		case 2:
		{
			rawImagePath = "C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\flower.png";
			break;
		}
		case 3:
		{
			rawImagePath = "C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\fight.png";
			break;
		}
		case 4:
		{
			rawImagePath = "C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\bread.png";
			break;
		}
		case 5:
		{
			rawImagePath = "C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\witch.png";
			break;
		}
		}

		if (rawImagePath == nullptr)
		{
			system("cls");
			choise = 0;
		}
	} while (choise == 0);

	uint n = 0;
	uint m = 0;
	system("cls");
	std::cout << "enter n (snippet height), m (snippet width) parameters: ";
	std::cin >> n >> m;

	uint p;
	system("cls");
	std::cout << "enter p (hidden layer neurons number, <= " << 2 * n * m * 3 << ") parameter: ";
	std::cin >> p;

	double e;
	std::cout << "enter e parameter: ";
	std::cin >> e;

	Image* image = new Image(n, m, rawImagePath);
	NeuralNetwork* nn = new NeuralNetwork(image, e, p);

	nn->run();

	cimg_library::CImg<uchar>* rawImage = new cimg_library::CImg<uchar>(rawImagePath);
	cimg_library_suffixed::CImgDisplay raw_disp(*rawImage, "raw"), result_disp(*image->getRaw(), "result");

	while (!raw_disp.is_closed() && !result_disp.is_closed())
	{
		raw_disp.wait();
		result_disp.wait();
	}

	//run_IOnDiffImages();
	//run_IOnZ();
}