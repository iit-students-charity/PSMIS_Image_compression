#include <iostream>

#include "util.h"
#include "Image.h"
#include "neural_network.h"


int main()
{
	const char* imagePath;
	uint choise;
	do
	{
		std::cout << "Choose an image: \n1. Girl\n2. Flower\n3. Fight";
		std::cin >> choise;
		imagePath = getImagePath(choise);

		if (imagePath == nullptr)
		{
			system("cls");
			choise = 0;
		}
	} while (choise == 0);

	uint p = 0;
	uint n = 0;
	uint m = 0;
	std::cout << "Enter n (snippet height), m (snippet width) parameters: ";
	std::cin >> n >> m;

	while (p > n / 2)
	{
		std::cout << "Enter p (<= " << n / 2 << ") parameter: ";
		std::cin >> p;
	}

	double e = 0;
	while (e > 0.1 * p)
	{
		std::cout << "Enter e (<= " << 0.1 * p << ") parameter: ";
		std::cin >> e;
	}

	Image* image = new Image(p, n, m, imagePath);
	NeuralNetwork* nn = new NeuralNetwork(image, e);
	
}

const char* getImagePath(uint choise)
{
	switch (choise)
	{
	case 1:
	{
		return "\\src\\girl.png";
	}
	case 2:
	{
		return "\\src\\flower.png";
	}
	case 3:
	{
		return "\\src\\fight.png";
	}
	default:
		return nullptr;
	}
}