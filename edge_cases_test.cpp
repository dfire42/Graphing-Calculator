#ifndef __EDGE_CASES_TEST_CPP__
#define __EDGE_CASES_TEST_CPP__

#include "gtest/gtest.h"
#include "../Graphing_Calculator/header/Interpreter.hpp"
#include "../Graphing_Calculator/header/handleOneVar.hpp"
#include "../Graphing_Calculator/src/removeParenthesis.cpp"

TEST(edgeCases, BaseVar) { 
    Interpreter* test = new Interpreter();
    HandleVars* result = test->getParsedEquation("x^x");
    EXPECT_EQ(4,result->getPoint("2"));

}

TEST(edgeCases, ConstantBase) {
    Interpreter* test = new Interpreter();
    HandleVars* result = test->getParsedEquation("(2*x)^2");
    EXPECT_EQ(16,result->getPoint("2"));
}

TEST(edgeCases, ParaVar) { 
    Interpreter* test = new Interpreter();
    HandleVars* result = test->getParsedEquation("(x+3)");
    EXPECT_EQ(16,result->getPoint("5"));
}

TEST(edgeCases, ParaVar2) {
    Interpreter* test = new Interpreter();
    HandleVars* result = test->getParsedEquation("(x)");
    EXPECT_EQ(2,result->getPoint("2"));
}

TEST(edgeCases, Decimal) {
    Interpreter* test = new Interpreter();
    HandleVars* result = test->getParsedEquation(".2");
    EXPECT_EQ(.2,result->getPoint("69"));

}

TEST(edgeCases, EmptyString) {
    Interpreter* test = new Interpreter();
    HandleVars* result = test->getParsedEquation("");
    EXPECT_EQ(0,result->getPoint("5"));
}

TEST(edgeCases, DollarSign) {
    Interpreter* test = new Interpreter();
    HandleVars* result = test->getParsedEquation("$");
    EXPECT_EQ(0,result->getPoint("5"));
}

TEST(edgeCases, EqualSign) {
    Interpreter* test = new Interpreter();
    HandleVars* result = test->getParsedEquation("=");
    EXPECT_EQ(0,result->getPoint("5"));
}

TEST(edgeCases, RidiculousAddSub) {
    Interpreter* test = new Interpreter();
    HandleVars* result = test->getParsedEquation("4-+-+-++-+--+++--+-+-+-+-+-+--4");
    EXPECT_EQ(0,result->getPoint("0"));
}

TEST(edgeCases, DigitRandomAlpha) {
    Interpreter* test = new Interpreter();
    HandleVars* result = test->getParsedEquation("4asdads$");
    EXPECT_EQ(0,result->getPoint("5"));
}

#endif
