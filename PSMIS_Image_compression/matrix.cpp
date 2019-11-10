#pragma once

#include <ctime>

#include "matrix.h"
#include <stdlib.h>


Matrix::Matrix(uint numberOfRows, uint numberOfColumns)
	: numberOfRows(numberOfRows), numberOfColumns(numberOfColumns) // not nedeed?
{
	if (numberOfRows == 0 || numberOfColumns == 0)
	{
		values = nullptr;
	}
	else
	{
		initRandom(numberOfRows, numberOfColumns);
	}
}

Matrix::Matrix(vector<vector<double>>* values, uint numberOfRows, uint numberOfColumns)
	: numberOfRows(numberOfRows), numberOfColumns(numberOfColumns)
{
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
	return values->at(rowNumber).at(columnNumber);
}

void Matrix::setValue(uint rowNumber, uint columnNumber, double value)
{
	values->at(rowNumber).at(columnNumber) = value;
}

const vector<double>* Matrix::getRowVector(uint numberOfRow) const
{
	return &values->at(numberOfRow);
}

const vector<double>* Matrix::getColumnVector(uint numberOfColumn) const
{
	return nullptr;
}

bool Matrix::sizecmp(Matrix* a, Matrix* b) 
{
	return (b->getNumberOfRows() != a->getNumberOfRows())
		|| (b->getNumberOfColumns() != (a->getNumberOfColumns())) ?
		false :
		true;
}


void Matrix::initRandom(uint numberOfRows, uint numberOfColumns)
{
	this->values = new vector<vector<double>>();
	this->values->resize(numberOfRows);

	srand(time(0));
	int multiplier = 100.;

	for (int row = 0; row < numberOfRows; row++)
	{
		values->at(row).resize(numberOfColumns);

		for (int col = 0; col < numberOfColumns; col++)
		{
			int rand_ = rand() % ((int)multiplier * 2 + 1);
			values->at(row).at(col) = (double)(-multiplier + rand_) / multiplier;
		}
	}
}

vector<vector<double>>* Matrix::transposeValues()
{
	vector<vector<double>>* newValues = new vector<vector<double>>();
	newValues->resize(numberOfColumns);

	for (int row = 0; row < numberOfColumns; row++)
	{
		newValues->at(row).resize(numberOfRows);
	}
	for (int row = 0; row < numberOfRows; row++)
	{
		for (int col = 0; col < numberOfColumns; col++)
		{
			newValues->at(col).at(row) = values->at(row).at(col);
		}
	}

	return newValues;
}

Matrix* Matrix::subtract(Matrix* a, Matrix* b)
{
	if (Matrix::sizecmp(a, b))
	{
		vector<vector<double>>* newValues = new vector<vector<double>>();
		newValues->resize(a->getNumberOfRows());

		uint rows = a->getNumberOfRows();
		uint cols = a->getNumberOfColumns();

		for (int row = 0; row < rows; row++)
		{
			newValues->at(row).resize(cols);
		}

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				newValues->at(row).at(col) = a->getValue(row, col) - b->getValue(row, col);
			}
		}

		return new Matrix(newValues, rows, cols);
	}

	return nullptr;
}

Matrix* Matrix::multiply(Matrix* a, Matrix* b)
{
	if (a->getNumberOfColumns() != b->getNumberOfRows())
	{
		return nullptr;
	}

	vector<vector<double>>* newValues = new vector<vector<double>>();
	newValues->resize(a->getNumberOfRows());
	uint rows = a->getNumberOfRows();
	uint cols = b->getNumberOfColumns();

	for (int row = 0; row < rows; row++)
	{
		newValues->at(row).resize(cols);
	}

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			for (int innerCol = 0; innerCol < a->getNumberOfColumns(); innerCol++)
			{
				newValues->at(row).at(col) += a->getValue(row, innerCol) * b->getValue(innerCol, col);
			}
		}
	}

	return new Matrix(newValues, rows, cols);
}

Matrix* Matrix::multiply(double number)
{
	vector<vector<double>>* newValues = new vector<vector<double>>();
	newValues->resize(numberOfRows);
	for (int row = 0; row < numberOfRows; row++)
	{
		newValues->at(row).resize(numberOfColumns);
	}

	for (int row = 0; row < numberOfRows; row++)
	{
		for (int col = 0; col < numberOfColumns; col++)
		{
			newValues->at(row).at(col) = number * values->at(row).at(col);
		}
	}

	return new Matrix(newValues, numberOfRows, numberOfColumns);
}

Matrix::~Matrix()
{
	if (values == nullptr)
	{
		return;
	}

	delete values;
}