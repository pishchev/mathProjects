#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <fstream>


#include "Matrix.hpp"

Matrix diagonal0(size_t n, double val = 1.0)
{
	Matrix m{ n };
	for (size_t i = 0; i < m.getRow(); i++)
	{
		for (size_t k = 0; k < m.getCol(); k++)
		{
			if (i != k) m.set(i, k, val);
		}
	}
	return m;
}

Matrix diagonal1(size_t n, double val = 1.0)
{
	Matrix m{ n };
	for (size_t i = 0; i < m.getRow(); i++)
	{
		for (size_t k = 0; k < m.getCol(); k++)
		{
			if (i == k) m.set(i, k, val);
		}
	}
	return m;
}

void DeterminantTest(std::ostream& stream)
{
	stream << "DETERM:" << std::endl;
	auto threads = { 1, 2, 3, 4 ,5,6,7,8,9};

	#ifdef _DEBUG
	auto dimensions = {100,150,160,170};
	#else
	auto dimensions = { 10, 20, 30, 50, 100,200,300 };
	#endif // _DEBUG

	stream << std::setw(6) << "dim" << ";";
	for (auto th : threads) {
		stream << std::setw(12) << th << ";";
	}
	stream << std::endl;
	stream << std::setprecision(7);
	for (auto dim : dimensions) {
		auto d = diagonal0(dim);
		double prev_det = std::numeric_limits<double>::max();
		stream << std::setw(6) << d.getCol() << ";"; stream.flush();
		for (auto th : threads) {
			d.setThreads(th);
			auto start = std::chrono::high_resolution_clock::now();
			auto det = d.det();
			stream << std::setw(12) << std::fixed << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() << ";"; stream.flush();
			if (prev_det != std::numeric_limits<double>::max() && prev_det != det) {
				stream << std::endl << "ERROR: calculation current det = " << std::defaultfloat << det << " != prev det = "; stream.flush();
				break;
			}
			prev_det = det;
		}
		stream <<std::endl;
	}
}

void SumTest(std::ostream& stream)
{
	stream << "Sum:" << std::endl;
	auto threads = { 1, 2, 3, 4 ,5,6,7,8,9 };

	#ifdef _DEBUG
	auto dimensions = { 100,150,170,180,200};
	#else
	auto dimensions = { 10, 20, 30, 50, 100,200,300 };
	#endif // _DEBUG

	stream << std::setw(6) << "dim" << ";";
	for (auto th : threads) {
		stream << std::setw(12) << th << ";";
	}
	stream << std::setw(10)  << std::endl;
	stream << std::setprecision(7);
	for (auto dim : dimensions) {
		auto d1 = diagonal1(dim);
		auto d2 = diagonal1(dim);
		stream << std::setw(6) << d1.getCol() << ";"; stream.flush();
		for (auto th : threads) {
			d1.setThreads(th);

			double time = INFINITY;
			for (int i = 0; i < 5; i++)
			{
				auto d3(d1);
				auto start = std::chrono::high_resolution_clock::now();
				d3 -= d2;
				auto end = std::chrono::high_resolution_clock::now();

				if (d3 != Matrix::Matrix(dim)) {
					stream << std::endl << "ERROR: calculation"; stream.flush();
					break;
				}

				auto res_time = std::chrono::duration<double>(end - start).count();
				time = res_time < time ? res_time : time;
			}
			stream << std::setw(12) << std::fixed << time << ";"; stream.flush();
		}
		stream <<std::endl;
	}
}

void MinTest(std::ostream& stream)
{
	stream << "Subtraction:" << std::endl;
	auto threads = { 1, 2, 3, 4 ,5,6,7,8,9 };

	#ifdef _DEBUG
	auto dimensions = { 10, 20, 30, 50, 100,200,300 };
	#else
	auto dimensions = { 10, 20, 30, 50, 100,200,300 };
	#endif // _DEBUG


	stream << std::setw(6) << "dim" << ";";
	for (auto th : threads) {
		stream << std::setw(12) << th << ";";
	}
	stream << std::endl;
	stream << std::setprecision(7);
	for (auto dim : dimensions) {
		auto d1 = diagonal1(dim);
		auto d2 = diagonal1(dim);
		stream << std::setw(6) << d1.getCol() << ";"; stream.flush();
		for (auto th : threads) {
			d1.setThreads(th);

			double time = INFINITY;
			for (int i = 0; i < 5; i++)
			{
				auto d3(d1);
				auto start = std::chrono::high_resolution_clock::now();
				d3 -= d2;
				auto end = std::chrono::high_resolution_clock::now();

				if (d3 != Matrix::Matrix(dim)) {
					stream << std::endl << "ERROR: calculation"; stream.flush();
					break;
				}

				auto res_time = std::chrono::duration<double>(end - start).count();
				time = res_time < time ? res_time : time;
			}
			stream << std::setw(12) << std::fixed << time << ";"; stream.flush();
		}
		stream << std::endl;
	}
}

void MultTest(std::ostream& stream)
{
	stream << "Mult:" << std::endl;
	auto threads = { 1, 2, 3, 4 ,5,6,7,8,9 };

	#ifdef _DEBUG
	auto dimensions = { 10, 20, 30, 50, 100,200,300};
	#else
	auto dimensions = { 10, 20, 30, 50, 100,200,300 };
	#endif // _DEBUG


	stream << std::setw(6) << "dim" << ";";
	for (auto th : threads) {
		stream << std::setw(12) << th << ";";
	}
	stream << std::endl;
	stream << std::setprecision(7);
	for (auto dim : dimensions) {
		auto d1 = diagonal1(dim);
		auto d2 = diagonal1(dim);
		stream << std::setw(6) << d1.getCol() << ";"; stream.flush();
		for (auto th : threads) {
			d1.setThreads(th);
			auto d3(d1);
			auto start = std::chrono::high_resolution_clock::now();
			d3 *= d2;
			stream << std::setw(12) << std::fixed << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() << ";"; stream.flush();
			if (d3 != diagonal1(dim)) {
				stream << std::endl << "ERROR: calculation"; stream.flush();
				break;
			}
		}
		stream << std::endl;
	}
}


int main()
{
	std::fstream file;
	//file.open("Tests\\test_release_mult.txt", 'w');
	std::ostream& st = std::cout;

	/*DeterminantTest(st);
	std::cout << "Determ test finished" << std::endl;

	SumTest(st);
	std::cout << "Sum test finished" << std::endl;

	MinTest(st);
	std::cout << "Minus test finished" << std::endl;

	MultTest(st);
	std::cout << "Mult test finished" << std::endl;*/

	//file.close();

	
	system("pause");
	return 0;
}