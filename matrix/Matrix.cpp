#include "Matrix.hpp"

#include <future>
#include <iostream>
#include <mutex>
#include <thread>

int Matrix::amount_threads = -1;

bool Matrix::is_correct(const Matrix& matr)
{
	if (matr.getRow() == 0 || matr.getCol() == 0)
	{
		return false;
	}
	return true;
}

Matrix::Matrix(size_t col) :Matrix(col, col) {}
Matrix::Matrix(size_t row, size_t col ) : col(col), row(row)
{
	if (col == 0 || row == 0)
	{
		throw Matrix_EX("Zero size");
	}
	matr.resize(row , std::vector<double>(col));
}
Matrix::Matrix(const matrix& matr2)
{
	matr = matr2;
	row = matr.size();
	col = matr[0].size();
	if (!is_correct(*this))
	{
		throw Matrix_EX("Incorrect matrix");
	}
}

void Matrix::set( size_t row, size_t col, double value)
{
	matr[row][col] = value;
}
double Matrix::get(size_t row, size_t col)
{
	return matr[row][col];
}

void Matrix::setThreads(size_t count)
{
	amount_threads =  static_cast<int>(count);
}
void Matrix::print() const
{
	std::cout << "------------------------------" << std::endl;
	for (size_t i = 0; i < row; i++)
	{
		for (size_t k = 0; k < col; ++k)
		{
			std::cout << matr[i][k] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "------------------------------" << std::endl;
}

size_t Matrix::getCol() const
{
	return col;
}
size_t Matrix::getRow() const
{
	return row;
}
const Matrix::matrix& Matrix::getMatrix()const
{
	return matr;
}

bool Matrix::operator==(const Matrix& matr2) const
{
	return matr == matr2.getMatrix();
}
bool Matrix::operator!=(const Matrix& matr2)const
{
	return !(*this == matr2);
}

void Matrix::mult_(Matrix& matr, const Matrix& matr1, const Matrix& matr2, size_t from, size_t to)
{
	size_t N = matr1.getCol();
	for (size_t m = from; m < to; ++m)
	{
		for (size_t k = 0; k < matr2.getCol(); ++k)
		{
			for (size_t n = 0; n < N; ++n)
			{
				matr.matr[m][k] += matr1.matr[m][n] * matr2.matr[n][k];
			}
		}
	}
}
void Matrix::sum_(Matrix& matr1, const Matrix& matr2, size_t from, size_t to)
{	
	size_t col = matr1.col;
	for (size_t i = from; i < to; i++)
	{
		for (size_t k = 0; k < col; k++)
		{
			matr1.matr[i][k] += matr2.getMatrix()[i][k];
		}
	}
}
void Matrix::subtraction_(Matrix& matr1, const Matrix& matr2, size_t from, size_t to)
{
	size_t col = matr1.getCol();
	for (size_t i = from; i < to; i++)
	{
		for (size_t k = 0; k < col; k++)
		{
			matr1.matr[i][k] -= matr2.getMatrix()[i][k];
		}
	}
}

Matrix Matrix::operator*(const Matrix& matr2) const
{
	Matrix matr1(*this);
	return matr1 *= matr2;
}
Matrix Matrix::operator+(const Matrix& matr2) const
{
	Matrix matr1(*this);
	return matr1+= matr2;
}
Matrix Matrix::operator-(const Matrix& matr2) const
{
	Matrix matr1(*this);
	return matr1 -= matr2;
}

Matrix& Matrix::operator*=(const Matrix& matr2)
{
	if (col != matr2.getRow())
	{
		throw Matrix_EX("Incorrect matrixs");
	}
	Matrix result(row, matr2.getCol());

	size_t amount_threads_ = 0;

	if (amount_threads < 0)
	{
		if (col >= mult_dim || row >= mult_dim)
		{
			amount_threads_ = optim_th;
		}
		else
		{
			amount_threads_ = 1;
		}
	}
	else
	{
		amount_threads_ = amount_threads;
	}
	std::vector<std::future<void>> threads;
	double k = static_cast<double>(row) / static_cast<double>(amount_threads_);
	for (size_t i = 0; i < amount_threads_; i++)
	{
		size_t from = static_cast<size_t>(std::round(static_cast<double>(i) * k));
		size_t to = static_cast<size_t>(std::round(static_cast<double>(i + 1) * k));
		if (i < amount_threads_ - 1)
		{
			threads.push_back(std::async(std::launch::async, mult_, std::ref(result), std::ref(*this), std::ref(matr2), from, to));
			continue;
		}
		mult_(result, *this,matr2, from, to);
	}
	for (size_t i_ = 0; i_ < threads.size(); i_++)
	{
		threads[i_].get();
	}
	*this = result;
	return *this;
}
Matrix& Matrix::operator+=(const Matrix& matr2)
{
	if (col != matr2.getCol() || row != matr2.getRow())
	{
		throw Matrix_EX("Sizes aren't equal");
	}

	size_t amount_threads_ = 0;

	if (amount_threads < 0 )
	{
		if (col >= sum_min_dim || row >= sum_min_dim)
		{
			amount_threads_ = optim_th;
		}
		else
		{
			amount_threads_ = 1;
		}
	}
	else
	{
		amount_threads_ = amount_threads;
	}

	std::vector<std::future<void>> threads;
	double k = static_cast<double>(row) / static_cast<double>(amount_threads_);
	for (size_t i = 0; i < amount_threads_; i++)
	{
		size_t from = static_cast<size_t>(std::round(static_cast<double>(i) * k));
		size_t to = static_cast<size_t>(std::round(static_cast<double>(i + 1) * k));

		if (i < amount_threads_ - 1)
		{
			threads.push_back(std::async(sum_, std::ref(*this), std::ref(matr2), from, to));
			continue;
		}
		sum_(*this, matr2, from, to);
	}
	for (size_t i_ = 0; i_ < threads.size(); i_++)
	{
		threads[i_].get();
	}
	return *this;
}
Matrix& Matrix::operator-=(const Matrix& matr2)
{
	if (col != matr2.getCol() || row != matr2.getRow())
	{
		throw Matrix_EX("Sizes aren't equal");
	}

	size_t amount_threads_ = 0;

	if (amount_threads < 0)
	{
		if (col >= sum_min_dim || row >= sum_min_dim)
		{
			amount_threads_ = optim_th;
		}
		else
		{
			amount_threads_ = 1;
		}
	}
	else
	{
		amount_threads_ = amount_threads;
	}

	std::vector<std::future<void>> threads;
	double k = static_cast<double>(row) / static_cast<double>(amount_threads_);
	for (size_t i = 0; i < amount_threads_; i++)
	{
		size_t from = static_cast<size_t>(std::round(static_cast<double>(i) * k));
		size_t to = static_cast<size_t>(std::round(static_cast<double>(i + 1) * k));

		if (i < amount_threads_ - 1)
		{
			threads.push_back(std::async(subtraction_, std::ref(*this), std::ref(matr2), from, to));
			continue;
		}
		subtraction_(*this, matr2, from, to);
	}
	for (size_t i_ = 0; i_ < threads.size(); i_++)
	{
		threads[i_].get();
	}
	return *this;
}

void Matrix::swap(size_t x, size_t y)
{
	matr[x].swap(matr[y]);
}

int Matrix::prep_diag(size_t x)
{
	if (matr[x][x] == 0)
	{
		for (size_t i = x + 1; i < row ; ++i)
		{
			if (matr[i][x] != 0)
			{
				swap(i, x);
				return  static_cast<int>( i - x);
			}
		}
		return -1;
	}
	return 0;
}

void Matrix::det_(Matrix& matr,size_t column, size_t from, size_t to)
{
	for (size_t k = from ; k < to; k++)
	{
		double mult = matr.matr[k][column] / matr.matr[column][column];
		for (size_t p = column; p < matr.getRow(); p++)
		{
			matr.matr[k][p] -= matr.matr[column][p] * mult;
		}
	}
}
double Matrix::det() const
{
	Matrix n_matrix(*this);

	if (col != row)
	{
		throw Matrix_EX("col != row");
	}
	if(col == 2)
	{
		return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
	}
	bool is_zero = false;
	int change = 0;

	for (size_t i = 0; i < col; i++)
	{
		int x = n_matrix.prep_diag(i);
		if (x == -1)
		{
			is_zero = true;
			break;
		}
		change += x;
		
		size_t amount_threads_ = 0;

		if (amount_threads < 0 )
		{
			if (col >= det_dim )
			{
				amount_threads_ = optim_th;
			}
			else
			{
				amount_threads_ = 1;
			}
		}
		else
		{
			amount_threads_ = amount_threads;
		}

		amount_threads_ = col - i < amount_threads_ ? col - i : amount_threads_;

		std::cout << amount_threads_ << std::endl;

		std::vector<std::future<void>> threads;
		double k = static_cast<double>(row - i - 1) / static_cast<double>(amount_threads_);
		for (size_t i_ = 0; i_ < amount_threads_; i_++)
		{	
			size_t from = static_cast<size_t>(std::round(static_cast<double>(i_) * k) +1+i);
			size_t to = static_cast<size_t>(std::round(static_cast<double>(i_ + 1) * k) +1+i);

			if (i_< amount_threads_ -1)
			{
				threads.push_back(std::async(std::launch::async, det_, std::ref(n_matrix), i, from, to));
				continue;
			}
			det_(n_matrix, i, from, to);
		}
		for (size_t i_ = 0; i_ < threads.size() ; i_++)
		{
			threads[i_].get();
		}
	}
	double result = 1;
	if (is_zero)
	{
		return 0;
	}
	for (size_t i = 0; i < col; i++)
	{
		result *= n_matrix.matr[i][i];
	}
	result = change % 2 == 0 ? result : (-result);
	return result;
}

