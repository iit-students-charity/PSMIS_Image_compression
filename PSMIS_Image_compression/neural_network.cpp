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
	var I = compressImage(inputImage);
	restoreImage(inputImage);

	System.out.println(String.format("L: %d. Z: %f. I: %d. Adaptive step: %f", L, Z, I, adaptiveStep));

}