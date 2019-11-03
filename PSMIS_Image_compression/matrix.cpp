#pragma once

#include "matrix.h"

Matrix::Matrix(uint numberOfRows = 0U, uint numberOfColumns = 0U)
	: numberOfRows(numberOfRows), numberOfColumns(numberOfColumns) // not nedeed?
{
	values = new double*[numberOfRows];
	for (int i = 0; i < numberOfRows; ++i)
	{
		values[i] = new double[numberOfColumns];
	}
}

Matrix::Matrix(double** values, uint numberOfRows = 0U, uint numberOfColumns = 0U)
	: Matrix(numberOfRows, numberOfColumns)
{
	/*for (int r = 0; r < row; r++) {
		if (matrix[r].length != column) {
			throw new IllegalArgumentException("Different rows' length.");
		}
	}*/
	this->values = values;
}

uint Matrix::getNumberOfRows() const
{
	return numberOfRows;
}

uint Matrix::getNumberOfColumns() const
{
	return numberOfColumns;
}

double Matrix::getValue(uint rowNumber, uint columnNumber) const
{
	return values[rowNumber][columnNumber];
}

void Matrix::setValue(uint rowNumber, uint columnNumber, double value)
{
	values[rowNumber][columnNumber] = value;
}

const double* Matrix::getRowVector(uint numberOfRow) const
{
	return values[numberOfRow];
}

const double* Matrix::getColumnVector(uint numberOfColumn) const
{
	return nullptr;
}

Matrix::~Matrix()
{
	for (uint rowNumber = 0; rowNumber < numberOfRows; rowNumber++)
	{
		delete[] values[rowNumber];
	}
	delete[] values;
	delete values;
}