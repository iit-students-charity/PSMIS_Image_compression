#include "neural_network.h"

NeuralNetwork::NeuralNetwork(Image* image, double e)
{
	this->inputImage = image;
	this->e = e;
}

void NeuralNetwork::run()
{
	uint L = inputImage->getTempHeight() * inputImage->getTempWidth();
	double Z = (double)(N * L) / ((N + L) * inputImage->getP() + 2);

	inputImage->initSnippets();
	var I = compressImage();
	restoreImage(); 

	System.out.println(String.format("L: %d. Z: %f. I: %d. Adaptive step: %f", L, Z, I, adaptiveStep));
}

void NeuralNetwork::restoreImage()
{
	//var image = image->getInputImage();

	ImageSnippet* snippets = inputImage->getSnippets();
	uint snippetWidth = inputImage->getM();
	uint snippetHeight = inputImage->getN();

	for (int snIndex; snIndex < inputImage->getSnippetsNumber(); snIndex++) {
		X = snippets[snIndex].getX0();
		Y = Matrix::multiply(*X, *W);
		X_ = Matrix::multiply(*Y, *W_);

		uint x = snippets[snIndex].getStartX();
		uint y = snippets[snIndex].getStartY();
		uint pixelPosition = 0;

		for (int i = 0; i < snippetWidth; i++)
		{
			for (int j = 0; j < snippetHeight; j++)
			{
				int red = snippets[snIndex].restoreColor(X_->getValue(0, pixelPosition++));
				int green = snippets[snIndex].restoreColor(X_->getValue(0, pixelPosition++));
				int blue = snippets[snIndex].restoreColor(X_->getValue(0, pixelPosition++));

				int* color = new int[3]{ red, green, blue };
				if (x + i < inputImage->getWidth())
				{
					if (y + j < inputImage->getHeight())
					{
						inputImage->setColor(x + i, y + j, color);
					}
				}
			}
		}
	}

	inputImage->save();
}