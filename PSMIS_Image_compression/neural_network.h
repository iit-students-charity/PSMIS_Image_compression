#pragma once

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "matrix.h"
#include "Image.h"


class NeuralNetwork
{
private:
	int N;

	double e;
	double adaptiveStep;

	Matrix* X;
	Matrix* X_;
	Matrix* Y;
	Matrix* W;
	Matrix* W_;

	Image* inputImage;

	void restore();
	int compress();
public:
	NeuralNetwork(Image* image, double e);

	void run();
};

#endif // NEURAL_NETWORK_H