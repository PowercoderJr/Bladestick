#pragma once

namespace Bladestick
{
	public ref class Matrix
	{
	internal:
		array<double> ^ m;
		int nRows, nCols;
	public:
		Matrix(int nRows, int nCols);
		Matrix ^ operator*(Matrix ^ a);
		double % operator()(int row, int col);
		int getRowsCount();
		int getColsCount();
	};
}
