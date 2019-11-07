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
	static const int ADAPTIVE_STEP_INITIAL_VALUE = 100;

	NeuralNetwork(Image* image, double e);
	
	void run();
	
	static double calculateAdaptiveStep(
		Matrix const* base, 
		Matrix const* transposed
	);
	
	static double calculateError(Matrix* deltaX, int length);
	
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