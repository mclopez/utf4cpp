cmake_minimum_required(VERSION 2.8 )
project(libutf4cpp)


ADD_LIBRARY(utf4cpp SHARED
cdb/grapheme_break.cpp	
cdb/word_break.cpp
cdb/sentence_break.cpp
cdb/line_break.cpp	
)


