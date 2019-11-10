#pragma once

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "matrix.h"
#include "Image.h"


class NeuralNetwork
{
private:
	uint hiddenNeuronsNumber;

	int N;

	double e;
	double adaptiveLearningRate;

	Matrix* X;
	Matrix* X_;
	Matrix* Y;
	Matrix* W;
	Matrix* W_;

	Image* inputImage;

	void restore();
	int compress();
public:
	NeuralNetwork(Image* image, double e, uint hiddenNeuronsNumber);
	
	void run();
	
	static double calculateAdaptiveLearningRate(Matrix const* base);
	
	static double calculateError(Matrix const* deltaX);
	
	static Matrix* prepareWeights(
		double learningStep_T, 
		Matrix* Y_T, 
		Matrix* deltaX
	);
	
	static Matrix* prepareWeights(
		double learningStep, 
		Matrix* X_T, 
		Matrix* deltaX, 
		Matrix* W_T
	);
};

#endif // NEURAL_NETWORK_H