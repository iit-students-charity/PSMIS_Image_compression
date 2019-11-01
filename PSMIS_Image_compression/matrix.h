#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include "util.h"

using namespace std;

class Matrix {
private:
	double** matrix;
public:
	const uint numberOfRows;
	const uint numberOfColumns;

	Matrix(int numberOfRows = 0, int numberOfColumns = 0);

	uint getNumberOfRows() const;
	uint getNumberOfColumns() const;

	double getValue(uint rowNumber, uint columnNumber) const;
	void setValue(uint rowNumber, uint columnNumber);

	const double* getHorizontalVector(uint numberOfRow) const;
	const double* getVerticalVector(uint numberOfColumn) const;

	~Matrix()
	{
		for (uint rowNumber = 0; rowNumber < numberOfRows; rowNumber++)
		{
			delete [] matrix[rowNumber];
		}
		delete [] matrix;
		delete matrix;
	}
};

#endif // MATRIX_H