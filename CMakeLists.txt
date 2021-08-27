CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)


ADD_EXECUTABLE(test
    Graphing_Calculator/src/equation.cpp
	Graphing_Calculator/src/Interpreter.cpp
	Graphing_Calculator/src/handleOneVar.cpp
	Testing/unit_test.cpp
	
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)