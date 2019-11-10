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

	uint p;
	system("cls");
	std::cout << "Enter p (hidden layer neurons number, <= " << 2 * n * m * 3 << ") parameter: ";
	std::cin >> p;

	double e;
	std::cout << "Enter e parameter: ";
	std::cin >> e;

	Image* image = new Image(n, m, imagePath);
	NeuralNetwork* nn = new NeuralNetwork(image, e, p);

	nn->run();
}