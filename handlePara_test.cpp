#ifndef __HANDLEPARA_TEST_CPP__
#define __HANDLEPARA_TEST_CPP__

#include "gtest/gtest.h"
#include "../Graphing_Calculator/header/Interpreter.hpp"
#include "../Graphing_Calculator/header/handleOneVar.hpp"
#include "../Graphing_Calculator/src/removeParenthesis.cpp"

TEST(handlePara, Basic) {
	string eq = "(x)";
	vector<int> inner;
	inner.push_back(0);
	inner.push_back(2);
	vector<vector<int>> location;
	location.push_back(inner);
	EXPECT_EQ("x",handleParenthesis(eq,location)); 
	
}

TEST(handlePara, Basic2) {
	string eq = "(x)(x)";
	vector<int> inner;
	vector<vector<int>> location;
	inner.push_back(0);
	inner.push_back(3);
	location.push_back(inner);
	inner.pop_back(); inner.pop_back();
	inner.push_back(4);
	inner.push_back(6);
	location.push_back(inner);
	EXPECT_EQ("x*x", handleParenthesis(eq,location));
}

TEST(handlePara, Complex) {
	string eq = "(x+2)(x-2)";
	vector<int> inner;
	vector<vector<int>> location;
	inner.push_back(0);
	inner.push_back(4);
	location.push_back(inner);
	inner.pop_back();
	inner.pop_back();
	inner.push_back(5);
	inner.push_back(9);
	location.push_back(inner);
	EXPECT_EQ("x*x+x*-2+2*x+2*-2", handleParenthesis(eq,location));

}

TEST(handlePara, Complex2) {
	string eq = "(x+4)(x+7)(x)";
	vector<int> inner;
	vector<vector<int>> location;
	inner.push_back(0);
	inner.push_back(4);
	location.push_back(inner);
	inner.pop_back();
	inner.pop_back();
	inner.push_back(5);
	inner.push_back(9);
	inner.pop_back();
	inner.pop_back();
	inner.push_back(10);
	inner.push_back(12);
	location.push_back(inner);
	EXPECT_EQ("x*x*x+x*x*4+7*x*x+4*7*x", handleParenthesis(eq,location));
}

#endif
