#include <iostream>

#include "util.h"
#include "Image.h"
#include "neural_network.h"


int main()
{
	const char* imagePath = nullptr;
	uint choise;
	do
	{
		std::cout << "Choose an image: \n1. Redhead\n2. Flower\n3. Fight\n";
		std::cin >> choise;

		switch (choise)
		{
		case 1:
		{
			imagePath = "C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\redhead.png";
			break;
		}
		case 2:
		{
			imagePath = "C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\flower.png";
			break;
		}
		case 3:
		{
			imagePath = "C:\\Users\\User\\source\\repos\\PSMIS_Image_compression\\PSMIS_Image_compression\\src\\fight.png";
			break;
		}
		}

		if (imagePath == nullptr)
		{
			system("cls");
			choise = 0;
		}
	} while (choise == 0);

	uint n = 0;
	uint m = 0;
	system("cls");
	std::cout << "Enter n (snippet height), m (snippet width) parameters: ";
	std::cin >> n >> m;

	uint p = n / 2 + 1;
	while (p > n / 2)
	{
		system("cls");
		std::cout << "Enter p (<= " << n / 2 << ") parameter: ";
		std::cin >> p;
	}

	double e = 0.1 * p + 1;
	while (e > 0.1 * p)
	{
		std::cout << "Enter e (<= " << 0.1 * p << ") parameter: ";
		std::cin >> e;
	}

	Image* image = new Image(p, n, m, imagePath);
	NeuralNetwork* nn = new NeuralNetwork(image, e);

	nn->run();
}