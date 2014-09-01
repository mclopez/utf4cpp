cmake_minimum_required(VERSION 2.8)
PROJECT(utf4cpp)
SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++0x")
#ADD_EXECUTABLE(automatas main.cpp reg_exp_test.cpp reg_exp.cpp)
ADD_SUBDIRECTORY(automatas)
ADD_SUBDIRECTORY(utils)



add_custom_command (
	OUTPUT utf4cpp/cdb/grapheme_break_binary_auto.h
  COMMAND utils -gb
  DEPENDS utils  
)

add_custom_command (
	OUTPUT utf4cpp/cdb/word_break_binary_auto.h
  COMMAND utils -wb
  DEPENDS utils  
)

add_custom_command (
	OUTPUT utf4cpp/cdb/sentence_break_binary_auto.h
  COMMAND utils -sb
  DEPENDS utils  
)


add_custom_command (
	OUTPUT utf4cpp/dfa/grapheme_break_dfa.h
  COMMAND utils -gdfa
  DEPENDS utils automatas  
)

add_custom_command (
	OUTPUT utf4cpp/dfa/word_break_dfa.h
  COMMAND utils -wdfa
  DEPENDS utils automatas  
)

add_custom_command (
	OUTPUT utf4cpp/dfa/sentence_break_dfa.h
  COMMAND utils -sdfa
  DEPENDS utils automatas  
)





add_custom_target (segmentation_properties  
		DEPENDS 
		utf4cpp/cdb/grapheme_break_binary_auto.h  
		utf4cpp/cdb/word_break_binary_auto.h
		utf4cpp/cdb/sentence_break_binary_auto.h

		utf4cpp/dfa/grapheme_break_dfa.h
		utf4cpp/dfa/word_break_dfa.h
		utf4cpp/dfa/sentence_break_dfa.h

)


ADD_SUBDIRECTORY(utf4cpp)



add_dependencies(utf4cpp segmentation_properties)


add_subdirectory(utf4cpp_test)

add_custom_command (
	OUTPUT run_cmd
  COMMAND utf4cpptest
  DEPENDS utf4cpptest  
)

add_custom_target (
	run
  DEPENDS 
	run_cmd  
)

