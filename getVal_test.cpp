#ifndef __GETVAL_TEST_HPP__
#define __GETVAL_TEST_HPP__

#include "gtest/gtest.h"
#include "../Graphing_Calculator/header/Interpreter.hpp"
#include "../Graphing_Calculator/header/handleOneVar.hpp"
#include "../Graphing_Calculator/src/removeParenthesis.cpp"

TEST(getVal, Add) {
	EXPECT_EQ("x",getVals("x+5")[0]);
}

TEST(getVal, ComplexAdd) {
	EXPECT_EQ("x",getVals("x+x+x+5+7+9")[0]);
}

TEST(getVal,Sub) {
	EXPECT_EQ("x",getVals("x-5")[0]);
}

TEST(getVal,ComplexSub) {
	EXPECT_EQ("x", getVals("x-5-x-x-6")[0]);
}

TEST(getVal,Pow) {
	EXPECT_EQ("x^5", getVals("x^5")[0]);
}

TEST(getVal,ComplexPow) {
	EXPECT_EQ("x^5^7^8", getVals("x^5^7^8")[0]);
}

TEST(getVal, Div) {
	EXPECT_EQ("x/2", getVals("x/2")[0]);
}

TEST(getVal, ComplexDiv) {
	EXPECT_EQ("x/3/x",getVals("x/3/x")[0]);
}

TEST(getVal, Mult) {
	EXPECT_EQ("x*5", getVals("x*5")[0]);
}

TEST(getVal,ComplexMult) {
	EXPECT_EQ("x*5*x*7*9", getVals("x*5*x*7*9")[0]);
}

TEST(getVal,ComplexAddMultPowSub) {
	EXPECT_EQ("x^2", getVals("x^2+3*x+1-5-x")[0]);
}

TEST(getVal, Decimals) {
	EXPECT_EQ(".2*x", getVals(".2*x")[0]);
}

TEST(getVal, Decimals2) {
	EXPECT_EQ("x*.2", getVals("x*.2")[0]);
}

#endif // __GETVAL_TEST_HPP__
