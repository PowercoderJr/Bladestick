#include "Matrix.h"

using namespace Bladestick;

Matrix::Matrix(int nRows, int nCols)
{
	if (nRows < 1 || nCols < 1)
		throw gcnew System::ArgumentException("Количество строк и количество столбцов должны быть строго больше нуля");
	this->nRows = nRows;
	this->nCols = nCols;
	this->m = gcnew array<double>(nRows * nCols);
}

Matrix ^ Matrix::operator*(Matrix ^ a)
{
	if (this->nCols != a->nRows)
		throw gcnew System::OperationCanceledException("Количество столбцов левой матрицы не соответствует количеству строк правой матрицы");

	Matrix ^ result = gcnew Matrix(this->nRows, a->nCols); 
	for (int i = 0; i < this->nRows; ++i)
		for (int j = 0; j < a->nCols; ++j)
		{
			double element = 0;
			for (int k = 0; k < this->nCols; ++k)
				element += this(i, k) * a(k, j);
			result(i, j) = element;
		}
	return result;
}

double % Matrix::operator()(int row, int col)
{
	if (row < 0 || row >= nRows || col < 0 || col >= nCols)
		throw gcnew System::ArgumentOutOfRangeException();
	return m[nCols * row + col];
}

int Matrix::getRowsCount()
{
	return nRows;
}

int Matrix::getColsCount()
{
	return nCols;
}
