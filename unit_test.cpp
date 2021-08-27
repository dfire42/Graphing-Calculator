#include "gtest/gtest.h"
#include "adjustLocation_test.cpp"	// works
//#include "edge_cases_test.cpp"		// works, as intended
#include "getVal_test.cpp"			// need update
//#include "handlePara_test.cpp"		// infinite loop?
#include "remove_spaces_test.cpp"	// works
#include  "distrOp_test.cpp"
#include "handleParaNum_test.cpp"

int main(int argc, char **argv) {
  	::testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}
