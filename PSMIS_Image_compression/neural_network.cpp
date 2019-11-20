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
	uint L = inputImage->getSnippetsVerticalCapacity() * inputImage->getSnippetsHorizontalCapacity();
	double Z = (N * L) / (double)((N + L) * hiddenNeuronsNumber + 2);

	int I = compress();
	restore();

	std::cout << "snippets count (L): " << L << ", compression coefficient (Z): " << Z 
		<< ", number of iterations (I): " << I << ", learning rate (alpha): " << learningRate;
}

double NeuralNetwork::calculateLearningRate(Matrix const* base)
{
	double sum = 0;
	for (int i = 0; i < base->getNumberOfColumns(); i++)
	{
		sum += base->getValue(0, i) * base->getValue(0, i);
	}
	return 1. / sum;
}

Matrix* NeuralNetwork::calculateWeightsDifferenceMember(
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

Matrix* NeuralNetwork::calculateWeightsDifferenceMember(double learningRate_, Matrix* transposedY, Matrix* deltaX)
{
	Matrix* firstMultiply = transposedY->multiply(learningRate_);
	return Matrix::multiply(firstMultiply, deltaX);
}

double NeuralNetwork::calculateError(Matrix const* deltaX)
{
	double error = 0.;

	for (int i = 0; i < deltaX->getNumberOfColumns(); i++)
	{
		error += deltaX->getValue(0, i) * deltaX->getValue(0, i);
	}

	return error;
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

	double learningRate_;
	uint iteration = 0;
	double E = std::numeric_limits<double>::max();

	vector<ImageSnippet*>* snippets = inputImage->getSnippets();
	uint sizeee = 0;

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

			//learningRate = calculateLearningRate(X);
			//learningRate_ = calculateLearningRate(Y);

			Matrix* WDifferenceMember = calculateWeightsDifferenceMember(
				0.0005, transposedX, deltaX,
				new Matrix(
					W_->transposeValues(),
					W_->getNumberOfColumns(),
					W_->getNumberOfRows()
				)
			);
			Matrix* W_DifferenceMember = calculateWeightsDifferenceMember(
				0.0005,
				transposedY,
				deltaX
			);

			W = Matrix::subtract(W, WDifferenceMember);
			W_ = Matrix::subtract(W_, W_DifferenceMember);
			E += calculateError(deltaX);

			delete transposedX;
			delete transposedY;

			delete WDifferenceMember;
			delete W_DifferenceMember;

			delete Y;
			delete X_;
			delete deltaX;

			sizeee += sizeof(W) + sizeof(W_);
		}

		cout << sizeof(sizeee);
		iteration++;
		cout << "iteration: " << iteration << ", error: " << E << '\n';
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
				
				delete[] color;
			}
		}

		delete Y;
		delete X_;
	}

	inputImage->save();
}
