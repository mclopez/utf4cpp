#cmake_minimum_required(VERSION 2.8)
#PROJECT(utf4cpp_test)
#SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++0x")

find_package( Boost REQUIRED COMPONENTS unit_test_framework )
include_directories( Boost_INCLUDE_DIRS )
INCLUDE_DIRECTORIES( .. )

ADD_EXECUTABLE(utf4cpptest
cdb_test.cpp
const_iterator_test.cpp  
input_output_test.cpp
main.cpp
segmentation_test.cpp
test_data.cpp
test_utf.cpp
util.cpp

)


TARGET_LINK_LIBRARIES(utf4cpptest
boost_unit_test_framework
utf4cpp
)

FIND_PACKAGE(Boost)
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})



