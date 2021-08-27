#ifndef __ADJUSTLOCATION_TEST_CPP__
#define __ADJUSTLOCATION_TEST_CPP__

#include "gtest/gtest.h"
#include "../Graphing_Calculator/header/Interpreter.hpp"
#include "../Graphing_Calculator/header/handleNoVars.hpp"
#include "../Graphing_Calculator/src/removeParenthesis.cpp"


TEST(adjustLocation, Complex2) {
	vector<int> inner;
	vector<vector<int>> location;
	inner.push_back(0);
	inner.push_back(3);
	location.push_back(inner);
	inner.pop_back(); inner.pop_back();
	inner.push_back(4);
	inner.push_back(6);
	location.push_back(inner);
	inner.pop_back(); inner.pop_back();
	inner.push_back(7);
	inner.push_back(10);
	location.push_back(inner);
	location = adjustLocation(location,-1,0);
	EXPECT_EQ(0,location[0][0]);
	EXPECT_EQ(2,location[0][1]);
	EXPECT_EQ(3,location[1][0]);
	EXPECT_EQ(5,location[1][1]);
	EXPECT_EQ(6,location[2][0]);
	EXPECT_EQ(9,location[2][1]);
}

TEST(adjustLocation, Basic) {
	vector<int> inner;
	vector<vector<int>> location;
	inner.push_back(0);
	inner.push_back(3);
	location.push_back(inner);
	inner.pop_back(); inner.pop_back();
	//inner.push_back(4);
	//inner.push_back(6);
	//location.push_back(inner);
	location = adjustLocation(location,-1,0);
	EXPECT_EQ(0,location[0][0]);
	EXPECT_EQ(2,location[0][1]);
	//EXPECT_EQ(5,location[1][1]);
	//EXPECT_EQ(0,location[1][2]);
}

#endif /*__ADJUSTLOCATION_TEST_CPP__ */
