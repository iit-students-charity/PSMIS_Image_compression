#pragma once

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "matrix.h"
#include "Image.h"


class NeuralNetwork
{
private:
	static const int RGB = 3;

	int N;

	double e;
	double adaptiveStep;

	Matrix* X;
	Matrix* X_;
	Matrix* Y;
	Matrix* W;
	Matrix* W_;

	Image* inputImage;
public:
	NeuralNetwork(Image* image, double e);

	void run();

	private void restoreImage(Image imageToRestore) {
		var image = imageToRestore.getInputImage();

		var rectangles = imageToRestore.getRectangles();
		var rectangleWidth = imageToRestore.getM();
		var rectangleHeight = imageToRestore.getN();
		var restoredImage = new BufferedImage(image.getWidth(), image.getHeight(), TYPE_3BYTE_BGR);

		for (var rectangle : rectangles) {
			X = rectangle.getX0();
			Y = multiply(X, W);
			X_ = multiply(Y, W_);

			var x = rectangle.getX();
			var y = rectangle.getY();
			var pixelPosition = 0;

			for (int i = 0; i < rectangleWidth; i++) {
				for (int j = 0; j < rectangleHeight; j++) {
					var red = rectangle.restorePixel(X_.getMatrix()[0][pixelPosition++]);
					var green = rectangle.restorePixel(X_.getMatrix()[0][pixelPosition++]);
					var blue = rectangle.restorePixel(X_.getMatrix()[0][pixelPosition++]);

					var color = new Color(red, green, blue);
					if (x + i < image.getWidth()) {
						if (y + j < image.getHeight()) {
							restoredImage.setRGB(x + i, y + j, color.getRGB());
						}
					}
				}
			}
		}
		saveImage(restoredImage);
	}

	private int compressImage(Image image) {
		W = new Matrix(init(N, image.getP()));
		W_ = new Matrix(transpose(W));

		Matrix deltaX;
		double adaptiveStep_T;
		var iteration = 0;
		var E = Double.MAX_VALUE;

		while (E > e) {
			E = 0;
			var rectangles = image.getRectangles();
			for (Rectangle rectangle : rectangles) {
				X = rectangle.getX0();
				Y = multiply(X, W);
				X_ = multiply(Y, W_);
				deltaX = subtract(X_, X);
				adaptiveStep = calculateAdaptiveStep(X, new Matrix(transpose(X)));
				adaptiveStep_T = calculateAdaptiveStep(Y, new Matrix(transpose(Y)));

				W = subtract(W, prepareWeights(adaptiveStep, new Matrix(transpose(X)), deltaX,
					new Matrix(transpose(W_))));
				W_ = subtract(W_, prepareWeights(adaptiveStep_T, new Matrix(transpose(Y)), deltaX));
				E += calculateError(deltaX, X.getMatrix()[0].length);
			}
			iteration++;
			System.out.println(E);
		}
		return iteration;
	}
};

#endif // NEURAL_NETWORK_H