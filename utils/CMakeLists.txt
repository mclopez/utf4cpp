#cmake_minimum_required(VERSION 2.8)
#PROJECT(utils)
#SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++0x")
include_directories(../automatas)

#ADD_SUBDIRECTORY(cdb)
#ADD_EXECUTABLE(utils main.cpp ${CDB_SRC})
#target_link_libraries( utils cdb )ADD_EXECUTABLE(utils 

ADD_EXECUTABLE(utils 

cdb/info_parser.cpp
cdb/util.cpp
cdb/binary_generator.cpp
cdb/common_generator.cpp
cdb/table_generator.cpp

dfautil_v6_3_0.cpp
dfautil.cpp
main.cpp

)

