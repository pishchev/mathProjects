#include "pch.h"
#include "Matrix.hpp"

TEST(Sum, equal_dimen) {
	{
		Matrix m1({ {1,2,3},{7,5,2},{7,0,6} });
		Matrix m2({ {8,3,8},{2,5,7},{7,4,9} });
		Matrix m3({ {9,5,11},{9,10,9},{14,4,15} });
		ASSERT_TRUE(m1 + m2 == m3);
		ASSERT_TRUE((m1 += m2) == m3);

	}
	{
		Matrix m1({ {1,2,3,5,6},{5,2,7,5,2},{9,2,7,0,6},{9,3,7,5,1},{9,-9,6,2,8} });
		Matrix m2({ {8,4,8,3,8},{2,5,5,0,7},{-2,9,7,4,9} ,{-3,6,-8,3,5},{0,0,8,3,6} });
		Matrix m3({ {9,6,11,8,14},{7,7,12,5,9},{7,11,14,4,15},{6,9,-1,8,6},{9,-9,14,5,14} });
		ASSERT_TRUE(m1 + m2 == m3);
		ASSERT_TRUE((m1 += m2) == m3);
	}
}
TEST(Sum, diff_dimen) {
	{
		Matrix m1({ {1,2,3},{7,5,2} });
		Matrix m2({ {8,3,8},{2,5,7} });
		Matrix m3({ {9,5,11},{9,10,9} });
		ASSERT_TRUE(m1 + m2 == m3);
		ASSERT_TRUE((m1 += m2) == m3);
	}
	{
		Matrix m1({ {1,2,3},{5,2,7},{9,2,7},{9,3,7},{9,-9,6} });
		Matrix m2({ {8,4,8},{2,5,5},{-2,9,7} ,{-3,6,-8},{0,0,8} });
		Matrix m3({ {9,6,11},{7,7,12},{7,11,14},{6,9,-1},{9,-9,14} });
		ASSERT_TRUE(m1 + m2 == m3);
		ASSERT_TRUE((m1 += m2) == m3);
	}
}
TEST(Minus, diff_dimen) {
	{
		Matrix m1({ {1,2,3},{7,5,2} });
		Matrix m2({ {8,3,8},{2,5,7} });
		Matrix m3({ {9,5,11},{9,10,9} });
		ASSERT_TRUE(m1 == m3 - m2);
		ASSERT_TRUE(m1 == (m3 -= m2));
	}
	{
		Matrix m1({ {1,2,3},{5,2,7},{9,2,7},{9,3,7},{9,-9,6} });
		Matrix m2({ {8,4,8},{2,5,5},{-2,9,7} ,{-3,6,-8},{0,0,8} });
		Matrix m3({ {9,6,11},{7,7,12},{7,11,14},{6,9,-1},{9,-9,14} });
		ASSERT_TRUE(m1 == m3-m2);
		ASSERT_TRUE(m1 == (m3 -= m2));
	}
}
TEST(Minus, equal_dimen) {
	{
		Matrix m1({ {1,2,3},{7,5,2},{7,0,6} });
		Matrix m2({ {8,3,8},{2,5,7},{7,4,9} });
		Matrix m3({ {9,5,11},{9,10,9},{14,4,15} });
		ASSERT_TRUE(m1 == m3 - m2);
		ASSERT_TRUE(m1 == (m3 -= m2));
	}
	{
		Matrix m1({ {1,2,3,5,6},{5,2,7,5,2},{9,2,7,0,6},{9,3,7,5,1},{9,-9,6,2,8} });
		Matrix m2({ {8,4,8,3,8},{2,5,5,0,7},{-2,9,7,4,9} ,{-3,6,-8,3,5},{0,0,8,3,6} });
		Matrix m3({ {9,6,11,8,14},{7,7,12,5,9},{7,11,14,4,15},{6,9,-1,8,6},{9,-9,14,5,14} });
		ASSERT_TRUE(m1 ==m3-m2);
		ASSERT_TRUE(m1 == (m3 -= m2));
	}
}
TEST(Multipl, equal_dimen) {
	{
		Matrix m1({ {1,2,3},{7,5,2},{7,0,6} });
		Matrix m2({ {8,3,8},{2,5,7},{7,4,9} });
		Matrix m3({ {33,25,49},{80,54,109},{98,45,110} });
		ASSERT_TRUE(m3 == m1 * m2);
		ASSERT_TRUE(m3 == (m1 *= m2));
	}
	{
		Matrix m1({ {1,2,3,7},{7,5,2,4},{7,0,6,0},{7,9,0,4} });
		Matrix m2({ {8,3,8,4},{2,5,7,7},{7,4,9,2},{3,6,2,6} });
		Matrix m3({ {54,67,63,66},{92,78,117,91},{98,45,110,40},{86,90,127,115} });
		ASSERT_TRUE(m3 == m1 * m2);
		ASSERT_TRUE(m3 == (m1 *= m2));
	}
}
TEST(Multipl , diff_dimen)
{
	{
		Matrix m1({ {1,2,3},{7,5,2},{7,0,6},{3,8,-1},{7,0,65} });
		Matrix m2({ {8,3,8,4,5},{2,5,7,6,4},{7,4,9,6,3} });
		Matrix m3({ {33,25,49,34,22},{80,54,109,70,61},{98,45,110,64,53},{33,45,71,54,44},{511,281,641,418,230} });
		ASSERT_TRUE(m3 == m1 * m2);
		ASSERT_TRUE(m3 == (m1 *= m2));
	}
	{
		Matrix m1({ {2,4,6,7},{7,2,-8,0} });
		Matrix m2({ {4,3},{2,7},{5,4},{1,9} });
		Matrix m3({ {53,121},{-8,3} });
		ASSERT_TRUE(m3 == m1 * m2);
		ASSERT_TRUE(m3 == (m1 *= m2));
	}
}
TEST(Det , dimen_is_2)
{
	Matrix m({ {1,2},{3,4} });

	ASSERT_TRUE(m.det() == -2);
}
TEST(Det , diag_1)
{
	Matrix m({ { 1,0,0,0,0,0,0 }, { 0,1,0,0,0,0,0 }, { 0,0,1,0,0,0,0 }, { 0,0,0,1,0,0,0 }, { 0,0,0,0,1,0,0 }, { 0,0,0,0,0,1,0 }, { 0,0,0,0,0,0,1 } });
	ASSERT_EQ(1, m.det());
}
TEST(Det , diag_0)
{
	Matrix m{ 10 };
	for (size_t i = 0; i < m.getRow(); i++)
	{
		for (size_t k = 0; k < m.getCol(); k++)
		{
			if (i != k) m.set(i, k, 1);
		}
	}

	ASSERT_TRUE( -9 > m.det() - 0.000000000001 && -9 < m.det() + 0.000000000001 );
}
TEST(Det , zero_col_zero_row)
{
	Matrix m{ 10 };
	for (size_t i = 0; i < m.getRow(); i++)
	{
		for (size_t k = 0; k < m.getCol(); k++)
		{
			if (k == 0) m.set(i, k, 0);
			else if (i != k) m.set(i, k, 1);
		}
	}
	ASSERT_EQ(0, m.det());

	for (size_t i = 0; i < m.getRow(); i++)
	{
		for (size_t k = 0; k < m.getCol(); k++)
		{
			if (i == 0) m.set(i, k, 0);
			else if (i != k) m.set(i, k, 1);
		}
	}
	ASSERT_EQ(0, m.det());
}

