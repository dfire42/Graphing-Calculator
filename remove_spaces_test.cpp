#ifndef __REMOVE_SPACES_TEST_CPP__
#define __REMOVE_SPACES_TEST_CPP__

#include "gtest/gtest.h"
#include "../Graphing_Calculator/header/Interpreter.hpp"
#include "../Graphing_Calculator/header/handleOneVar.hpp"
#include "../Graphing_Calculator/src/removeParenthesis.cpp"


TEST(removeSpaces, BasicEQ) {
	string eq = "y = 2x";
	string temp = removeSpaces(eq);
	EXPECT_EQ("y=2x", temp);

}

TEST(removeSpaces, BasicEQ2) {
	string eq = "y = 3x + 8";
	EXPECT_EQ("y=3x+8", removeSpaces(eq));
}

TEST(removeSpaces, ExpEQ) {
	string eq = "y = 3x^2 + 7";
	EXPECT_EQ("y=3x^2+7", removeSpaces(eq));
}

TEST(removeSpaces, ParaEQ) {
	string eq = "y = 3(x + 6)";
	EXPECT_EQ("y=3(x+6)", removeSpaces(eq));
}

#endif	//__REMOVE_SPACES_TEST_CPP__
