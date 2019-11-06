#include <limits>
#include <iostream>

#include "neural_network.h"


NeuralNetwork::NeuralNetwork(Image* image, double e)
{
	N = image->getN() * image->getM() * 3;
	this->inputImage = image;
	this->e = e;
}

void NeuralNetwork::run()
{
	uint L = inputImage->getTempHeight() * inputImage->getTempWidth();
	double Z = (N * L) / (double)((N + L) * inputImage->getP() + 2);

	inputImage->initSnippets();
	int I = compress();
	restore(); 

	std::cout << "L: " << L << ". Z: " << Z << ". I: " << I << ". Adaptive step: " << adaptiveStep;
}

double NeuralNetwork::calculateAdaptiveStep(Matrix const* base, Matrix const* transposed)
{
	double step = (double)NeuralNetwork::ADAPTIVE_STEP_INITIAL_VALUE;
	for (int i = 0; i < base->getNumberOfColumns(); i++) { // !!!! [0].length
		step += base->getValue(0, i) * transposed->getValue(i, 0);
	}
	return 1 / (step);
}

Matrix* NeuralNetwork::prepareWeights(double learningStep, Matrix* X_T, Matrix* deltaX, Matrix* W_T)
{
	Matrix* firstMultiply = X_T->multiply(learningStep);
	Matrix* secondMultiply = Matrix::multiply(firstMultiply, deltaX);
	return Matrix::multiply(secondMultiply, W_T);
}

Matrix* NeuralNetwork::prepareWeights(double learningStep_T, Matrix* Y_T, Matrix* deltaX)
{
	Matrix* firstMultiply = Y_T->multiply(learningStep_T);
	return Matrix::multiply(firstMultiply, deltaX);
}

double NeuralNetwork::calculateError(Matrix* deltaX, int length)
{
	double e = 0.;

	for (int i = 0; i < length; i++)
	{
		e += deltaX->getValue(0, i) * deltaX->getValue(0, i);
	}

	return e;
}

int NeuralNetwork::compress()
{
	W = new Matrix(N, inputImage->getP());
	W_ = new Matrix(
		W->transposeValues(),
		W->getNumberOfRows(), 
		W->getNumberOfColumns()
	);

	Matrix* deltaX;
	double adaptiveStep_T;
	uint iteration = 0;
	double E = std::numeric_limits<double>::max();

	while (E > e) {
		E = 0;
		ImageSnippet* snippets = inputImage->getSnippets();
		for (int snIndex = 0; snIndex < inputImage->getSnippetsNumber(); snIndex++) {
			X = snippets[snIndex].getX0();
			Y = Matrix::multiply(X, W);
			X_ = Matrix::multiply(Y, W_);
			deltaX = Matrix::subtract(X_, X);
			adaptiveStep = calculateAdaptiveStep(X, new Matrix(X->transposeValues()));
			adaptiveStep_T = calculateAdaptiveStep(Y, new Matrix(Y->transposeValues()));

			W = Matrix::subtract(
				W, 
				prepareWeights(
					adaptiveStep, 
					new Matrix(X->transposeValues()), 
					deltaX,
					new Matrix(W_->transposeValues())
				)
			);
			W_ = Matrix::subtract(
				W_, 
				prepareWeights(
					adaptiveStep_T, 
					new Matrix(Y->transposeValues()), 
					deltaX
				)
			);
			E += calculateError(deltaX, X->getNumberOfColumns()); // !!!!!
		}

		iteration++;

		cout << E << ' ';
	}

	return iteration;
}

void NeuralNetwork::restore()
{
	ImageSnippet* snippets = inputImage->getSnippets();
	uint snippetWidth = inputImage->getM();
	uint snippetHeight = inputImage->getN();

	for (int snIndex = 0; snIndex < inputImage->getSnippetsNumber(); snIndex++)
	{
		X = snippets[snIndex].getX0();
		Y = Matrix::multiply(X, W);
		X_ = Matrix::multiply(Y, W_);

		uint x = snippets[snIndex].getStartX();
		uint y = snippets[snIndex].getStartY();
		uint pixelPosition = 0;

		for (int w = 0; w < snippetWidth; w++)
		{
			for (int h = 0; h < snippetHeight; h++)
			{
				int red = snippets[snIndex].restoreColor(X_->getValue(0, pixelPosition++));
				int green = snippets[snIndex].restoreColor(X_->getValue(0, pixelPosition++));
				int blue = snippets[snIndex].restoreColor(X_->getValue(0, pixelPosition++));

				int* color = new int[3]{ red, green, blue };
				if (x + w < inputImage->getWidth())
				{
					if (y + h < inputImage->getHeight())
					{
						inputImage->setColor(x + w, y + h, color);
					}
				}
			}
		}
	}

	inputImage->save();
}