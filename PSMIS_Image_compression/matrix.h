#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include "util.h"

using namespace std;

class Matrix {
private:
	double** values;

	const uint numberOfRows;
	const uint numberOfColumns;
	double** initRandom(uint numberOfRows = 0U, uint numberOfColumns = 0U);
public:
	Matrix(uint numberOfRows = 0U, uint numberOfColumns = 0U);
	Matrix(double** values, uint numberOfRows = 0U, uint numberOfColumns = 0U);

	uint getNumberOfRows() const;
	uint getNumberOfColumns() const;

	double getValue(uint rowNumber, uint columnNumber) const;
	void setValue(uint rowNumber, uint columnNumber, double value);

	const double* getRowVector(uint numberOfRow) const;
	const double* getColumnVector(uint numberOfColumn) const;

	double** transposeValues();
	Matrix* multiply(double number);

	static bool sizecmp(Matrix* a, Matrix* b);
	static Matrix* subtract(Matrix* a, Matrix* b);
	static Matrix* multiply(Matrix* a, Matrix* b);

	~Matrix();
};

#endif // MATRIX_H