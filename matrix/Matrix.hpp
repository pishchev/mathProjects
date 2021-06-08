#pragma once
#include <vector>
#include <exception>

/*

0.................col
...................
...................
...................
...................
...................
...................
row.................MN

*/

class Matrix_EX : public std::exception {
public:
	Matrix_EX() = delete;
	Matrix_EX(const char* what_) : std::exception(what_) {}
};
class Matrix {
public:
	using matrix = std::vector<std::vector<double>>;
	
	explicit Matrix(size_t col);
	Matrix(size_t row , size_t col);
	Matrix(const matrix& matr2);

	void set(size_t row, size_t col, double value);
	double get(size_t row, size_t col);

	void setThreads(size_t count);
	
	bool operator==(const Matrix& matr2)const;
	bool operator!=(const Matrix& matr2)const;

	Matrix& operator*=(const Matrix& matr2);
	Matrix& operator+=(const Matrix& matr2);
	Matrix& operator-=(const Matrix& matr2);
	
	Matrix operator*(const Matrix& matr2)const;
	Matrix operator+(const Matrix& matr2)const;
	Matrix operator-(const Matrix& matr2)const;
	double det() const;
	
	void print() const;
	
	size_t getCol()const;
	size_t getRow()const;

private:

	//оптимальное число потоков для всех операций, >4 замедляется
	static const size_t optim_th = 4;
	#ifdef _DEBUG
		static const  size_t det_dim = 150;
		static const  size_t sum_min_dim = 100;
		static const  size_t mult_dim = 20;
	#else
		static const  size_t det_dim = 250;
		static const  size_t sum_min_dim = 300;
		static const  size_t mult_dim = 50;
	#endif

	static int amount_threads;

	matrix matr;
	size_t col;
	size_t row;

	void swap(size_t x, size_t y);
	int prep_diag(size_t x);

	static bool is_correct(const Matrix& matr);

	const matrix& getMatrix() const;

	static void det_(Matrix& matr, size_t column, size_t from, size_t to);
	static void mult_(Matrix& matr, const Matrix& matr1, const Matrix& matr2, size_t from, size_t to);
	static void sum_(Matrix& matr1, const Matrix& matr2, size_t from, size_t to);
	static void subtraction_(Matrix& matr1, const Matrix& matr2, size_t from, size_t to);
};
