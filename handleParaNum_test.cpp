#ifndef __HANDLEPARA_TEST_CPP__
#define __HANDLEPARA_TEST_CPP__

#include "gtest/gtest.h"
#include "../Graphing_Calculator/header/Interpreter.hpp"
#include "../Graphing_Calculator/header/handleOneVar.hpp"
#include "../Graphing_Calculator/src/removeParenthesis.cpp"

TEST(handlePara, BasicAdd) {
      	string eq = "(2+5)";
        vector<int> inner;
        inner.push_back(0);
        inner.push_back(4);
        vector<vector<int>> location;
        location.push_back(inner);
        EXPECT_EQ("7",handleParenthesis(eq,location));

}

TEST(handlePara, BasicSub) {
      	string eq = "(2-5)";
        vector<int> inner;
        inner.push_back(0);
        inner.push_back(4);
        vector<vector<int>> location;
        location.push_back(inner);
        EXPECT_EQ("-3",handleParenthesis(eq,location));

}

TEST(handlePara, DubTripMult) {
        string eq = "(2)*(5)(9)";
        vector<int> inner;
        vector<vector<int>> location;
        inner.push_back(0);
        inner.push_back(2);
        location.push_back(inner);
        inner.pop_back(); inner.pop_back();
        inner.push_back(3);
        inner.push_back(5);
        location.push_back(inner);
	inner.pop_back(); inner.pop_back();
	EXPECT_EQ("10", handleParenthesis(eq,location));
        inner.push_back(6);
        inner.push_back(8);
        location.push_back(inner);
        EXPECT_EQ("90", handleParenthesis(eq,location));
}

TEST(handlePara, DubTripDiv) {
        string eq = "(50)/(5)/(2)";
        vector<int> inner;
        vector<vector<int>> location;
        inner.push_back(0);
        inner.push_back(3);
        location.push_back(inner);
        inner.pop_back(); inner.pop_back();
        inner.push_back(5);
        inner.push_back(7);
        location.push_back(inner);
	inner.pop_back(); inner.pop_back();
	EXPECT_EQ("10", handleParenthesis(eq,location));
        inner.push_back(9);
        inner.push_back(11);
        location.push_back(inner);
        EXPECT_EQ("5", handleParenthesis(eq,location));
}

TEST(handlePara, SubAddDivMult) {
        string eq = "((2-4)+6)/(2)*(6)";
        vector<int> inner;
        vector<vector<int>> location;
        inner.push_back(1);
        inner.push_back(4);
        location.push_back(inner);
        inner.pop_back();inner.pop_back();
        inner.push_back(0);
        inner.push_back(7);
        location.push_back(inner);
	inner.pop_back();inner.pop_back();
	inner.push_back(9);
	inner.push_back(11);
	location.push_back(inner);
	inner.pop_back();inner.pop_back();
	inner.push_back(13);
	inner.push_back(15);
	location.push_back(inner);
	inner.pop_back();inner.pop_back();
        EXPECT_EQ("12", handleParenthesis(eq,location));

}


#endif

