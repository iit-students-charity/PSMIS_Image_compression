#pragma once

#include <ctime>

#include "matrix.h"
#include <stdlib.h>


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

bool Matrix::sizecmp(Matrix a, Matrix b) 
{
	return (b.getNumberOfRows() != a.getNumberOfRows())
		|| (b.getNumberOfColumns() != (a.getNumberOfColumns())) ?
		false :
		true;
}


double** Matrix::initRandom(uint numberOfRows = 0U, uint numberOfColumns = 0U)
{
	double** values = new double*[numberOfRows];

	srand(time(0));
	uint multiplier = 1000000;

	for (int row = 0; row < numberOfRows; row++)
	{
		values[row] = new double[numberOfColumns];

		for (int col = 0; col < numberOfColumns; col++)
		{
			values[row][col] = (-multiplier + rand() % multiplier) / multiplier;
		}
	}

	return values;
}

double** Matrix::transposeValues() {
	double** newValues = new double*[numberOfColumns];
	const double** oldValues = values;

	for (int row = 0; row < numberOfColumns; row++)
	{
		newValues[row] = new double[numberOfRows];
	}
	for (int row = 0; row < numberOfRows; row++)
	{
		for (int col = 0; col < numberOfColumns; col++)
		{
			newValues[col][row] = oldValues[row][col];
		}
	}

	return newValues;
}

Matrix* Matrix::subtract(Matrix a, Matrix b) {
	if (Matrix::sizecmp(a, b)) {
		double** newValues = new double* [a.getNumberOfRows()];
		uint rows = a.getNumberOfRows();
		uint cols = a.getNumberOfColumns();

		for (int row = 0; row < rows; row++)
		{
			newValues[row] = new double[cols];
		}

		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				newValues[row][col] = a.getValue(row, col) - b.getValue(row, col);
			}
		}
		return new Matrix(newValues, rows, cols);
	}

	return nullptr;
}

Matrix* Matrix::multiply(Matrix a, Matrix b)
{
	if (a.getNumberOfColumns() != b.getNumberOfRows())
	{
		return nullptr;
	}

	double** newValues = new double*[a.getNumberOfRows()];
	uint rows = a.getNumberOfRows();
	uint cols = b.getNumberOfColumns();

	for (int row = 0; row < rows; row++)
	{
		newValues[row] = new double[cols];
	}

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			for (int innerCol = 0; innerCol < a.getNumberOfColumns(); innerCol++)
			{
				newValues[row][col] += a.getValue(row, innerCol) * a.getValue(innerCol, col);
			}
		}
	}

	return new Matrix(newValues);
}

Matrix* Matrix::multiply(double number)
{
	double** newValues = new double*[numberOfRows];
	for (int row = 0; row < numberOfRows; row++)
	{
		newValues[row] = new double[numberOfColumns];
	}

	for (int row = 0; row < numberOfRows; row++)
	{
		for (int col = 0; col < numberOfColumns; col++)
		{
			newValues[row][col] = number * values[row][col];
		}
	}

	return new Matrix(newValues);
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