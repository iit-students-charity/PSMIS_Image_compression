#include <limits>
#include <iostream>

#include "neural_network.h"


NeuralNetwork::NeuralNetwork(Image* image, double e, uint hiddenNeuronsNumber)
{
	N = image->getN() * image->getM() * 3; 
	this->e = e;
	this->hiddenNeuronsNumber = hiddenNeuronsNumber;

	this->inputImage = image;
}

void NeuralNetwork::run()
{
	uint L = inputImage->getTempHeight() * inputImage->getTempWidth();
	double Z = (N * L) / (double)((N + L) * hiddenNeuronsNumber + 2);

	int I = compress();
	restore(); 

	std::cout << "L: " << L << ". Z: " << Z << ". I: " << I << ". Adaptive step: " << adaptiveLearningRate;
}

double NeuralNetwork::calculateAdaptiveLearningRate(Matrix const* base)
{
	double sum = 0;
	for (int i = 0; i < base->getNumberOfColumns(); i++)
	{
		sum += base->getValue(0, i) * base->getValue(0, i);
	}
	return 1. / sum;
}

Matrix* NeuralNetwork::prepareWeights(
	double learningRate, Matrix* transposedX, 
	Matrix* deltaX, Matrix* transposedW_
)
{
	Matrix* firstMultiply = transposedX->multiply(learningRate);
	Matrix* secondMultiply = Matrix::multiply(firstMultiply, deltaX);
	Matrix* result = Matrix::multiply(secondMultiply, transposedW_);

	delete firstMultiply;
	delete secondMultiply;

	return result;
}

Matrix* NeuralNetwork::prepareWeights(double learningRate_, Matrix* transposedY, Matrix* deltaX)
{
	Matrix* firstMultiply = transposedY->multiply(learningRate_);
	return Matrix::multiply(firstMultiply, deltaX);
}

double NeuralNetwork::calculateError(Matrix const* deltaX)
{
	double e = 0.;

	for (int i = 0; i < deltaX->getNumberOfColumns(); i++)
	{
		e += deltaX->getValue(0, i) * deltaX->getValue(0, i);
	}

	return e;
}

int NeuralNetwork::compress()
{
	W = new Matrix(N, hiddenNeuronsNumber);
	W_ = new Matrix(
		W->transposeValues(),
		W->getNumberOfColumns(),
		W->getNumberOfRows()
	);

	Matrix* deltaX;

	double adaptiveLearningRate_;
	uint iteration = 0;
	double E = std::numeric_limits<double>::max();

	vector<ImageSnippet*>* snippets = inputImage->getSnippets();

	while (E > e)
	{
		E = 0;
		for (int snIndex = 0; snIndex < inputImage->getSnippetsNumber(); snIndex++)
		{
			X = snippets->at(snIndex)->getX0();
			Y = Matrix::multiply(X, W);
			X_ = Matrix::multiply(Y, W_);
			deltaX = Matrix::subtract(X_, X);

			Matrix* transposedX = new Matrix(
				X->transposeValues(),
				X->getNumberOfColumns(),
				X->getNumberOfRows()
			);
			Matrix* transposedY = new Matrix(
				Y->transposeValues(),
				Y->getNumberOfColumns(),
				Y->getNumberOfRows()
			);

			adaptiveLearningRate = calculateAdaptiveLearningRate(X);
			adaptiveLearningRate_ = calculateAdaptiveLearningRate(Y);

			Matrix* preparedWeightsW = prepareWeights(
				adaptiveLearningRate, transposedX, deltaX,
				new Matrix(
					W_->transposeValues(),
					W_->getNumberOfColumns(),
					W_->getNumberOfRows()
				)
			);
			Matrix* preparedWeightsW_ = prepareWeights(
				adaptiveLearningRate_,
				transposedY,
				deltaX
			);

			W = Matrix::subtract(W, preparedWeightsW);
			W_ = Matrix::subtract(W_, preparedWeightsW_);
			E += calculateError(deltaX);

			delete transposedX;
			delete transposedY;

			delete preparedWeightsW;
			delete preparedWeightsW_;

			delete Y;
			delete X_;
			delete deltaX;
		}

		iteration++;
		cout << E << ' ';
	}

	return iteration;
}

void NeuralNetwork::restore()
{
	vector<ImageSnippet*>* snippets = inputImage->getSnippets();
	uint snippetWidth = inputImage->getM();
	uint snippetHeight = inputImage->getN();

	for (int snIndex = 0; snIndex < inputImage->getSnippetsNumber(); snIndex++)
	{
		X = snippets->at(snIndex)->getX0();
		Y = Matrix::multiply(X, W);
		X_ = Matrix::multiply(Y, W_);

		uint x = snippets->at(snIndex)->getStartX();
		uint y = snippets->at(snIndex)->getStartY();
		uint pixelPosition = 0;

		for (int w = 0; w < snippetWidth; w++)
		{
			for (int h = 0; h < snippetHeight; h++)
			{
				int red = snippets->at(snIndex)->restoreColor(X_->getValue(0, pixelPosition++));
				int green = snippets->at(snIndex)->restoreColor(X_->getValue(0, pixelPosition++));
				int blue = snippets->at(snIndex)->restoreColor(X_->getValue(0, pixelPosition++));

				int* color = new int[3]{ red, green, blue };
				if (x + w < inputImage->getWidth())
				{
					if (y + h < inputImage->getHeight())
					{
						inputImage->setColor(x + w, y + h, color);
					}
				}
				
				delete color;
			}
		}

		delete Y;
		delete X_;
	}

	inputImage->save();
}
