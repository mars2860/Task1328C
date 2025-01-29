project(Task1328C_Tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test1 test1.cpp)
add_executable(test2 test2.cpp)

add_test(NAME TernaryNumber::operator== COMMAND test1)
add_test(NAME TernaryNumber::operator^  COMMAND test2)
add_test(NAME RunInput.txt COMMAND Task1328C input.txt output.txt WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME CheckAnswer COMMAND fc output.txt answer.txt  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
