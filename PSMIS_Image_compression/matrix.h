#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

#include "util.h"

using namespace std;


class Matrix {
private:
	vector<vector<double>>* values;

	const uint numberOfRows;
	const uint numberOfColumns;

	void initRandom(uint numberOfRows, uint numberOfColumns);
public:
	Matrix(uint numberOfRows = 0U, uint numberOfColumns = 0U);
	Matrix(vector<vector<double>>* values, uint numberOfRows = 0U, uint numberOfColumns = 0U);

	uint getNumberOfRows() const;
	uint getNumberOfColumns() const;

	double getValue(uint rowNumber, uint columnNumber) const;
	void setValue(uint rowNumber, uint columnNumber, double value);

	const vector<double>* getRowVector(uint numberOfRow) const;
	const vector<double>* getColumnVector(uint numberOfColumn) const;

	vector<vector<double>>* transposeValues();
	Matrix* multiply(double number);

	static bool sizecmp(Matrix* a, Matrix* b);
	static Matrix* subtract(Matrix* a, Matrix* b);
	static Matrix* multiply(Matrix const* a, Matrix const* b);

	~Matrix();
};

#endif // MATRIX_H