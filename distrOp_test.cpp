#ifndef __DISTROP_TEST_CPP__
#define __DISTROP_TEST_CPP__

#include "gtest/gtest.h"
#include "../Graphing_Calculator/header/Interpreter.hpp"
#include "../Graphing_Calculator/header/handleNoVars.hpp"
#include "../Graphing_Calculator/src/removeParenthesis.cpp"

TEST(distrNeg,OneNeg) {
	string eq = "-2";
	EXPECT_EQ("+2", distributeNeg(eq));
}

TEST(distrNeg,NegPos) {
	string eq = "-2+3";
	EXPECT_EQ("+2-3", distributeNeg(eq));
}

TEST(distrNeg,DubNeg) {
	string eq = "-2-3";
	EXPECT_EQ("+2+3", distributeNeg(eq));
}

TEST(distrNeg,TripNegTripPara) {
	string eq = "-2-3-4";
	EXPECT_EQ("+2+3+4",distributeNeg(eq));
}

TEST(distrNeg, Mult) {
	string eq = "3*4";
	EXPECT_EQ("-3*4",distributeNeg(eq));
}

TEST(distrNeg, Div) {
	string eq = "3/4";
	EXPECT_EQ("-3/4",distributeNeg(eq));
}

TEST(distrNeg, MultDiv) {
	string eq = "3/4*5";
	EXPECT_EQ("-3/4*5",distributeNeg(eq));
}

TEST(distrMult,OneVar) {
	EXPECT_EQ("2*x+2*3", distributeMult("2","x+3"));
}

TEST(distrMult,OneVar2) {
	EXPECT_EQ("2*x", distributeMult("2","x"));
}

TEST(distrMult,OneVarComplex) {
	EXPECT_EQ("2*2x+2*9", distributeMult("2","2x+9"));
}

TEST(distrMult,TwoVarComplex) {
	EXPECT_EQ("x*x+x*3", distributeMult("x","x+3"));
}

TEST(distrMult,TripVarComplex) {
	string eq = distributeMult("x","x+3");
	string eq2 = distributeMult(eq,"x");
	EXPECT_EQ("x*x+x*3", eq);
	EXPECT_EQ("x*x*x+x*3*x", eq2);
}

TEST(distrPow, OneVar3) {
	EXPECT_EQ("x^5", distributePow("x","5"));
}

TEST(distrPow, OneVar4) {
	EXPECT_EQ("x^6",distributePow("x","5+1"));
}

TEST(distrPow, PowMult) {
	string eq = distributePow("x","5+1");
	EXPECT_EQ("x^6",eq);
	EXPECT_EQ("x*x^6", distributeMult("x",eq));
}

TEST(distrPow, DubVar2) {
	EXPECT_EQ("(x+1)^2","(x+1)^2");
}

#endif /*_DISTROP_TEST_CPP__*/
