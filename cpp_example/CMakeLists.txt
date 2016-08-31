cmake_minimum_required(VERSION 2.6)
 
Project(boost_example)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
FIND_PACKAGE(Boost)
#set(Boost_USE_MULTITHREADED ON) # which is the default
FIND_PACKAGE(Boost  COMPONENTS program_options required)

LINK_DIRECTORIES(
    ${LINK_DIRECTORIES} 
    ${Boost_LIBRARY_DIRS}
    
)

INCLUDE_DIRECTORIES(
    ${INCLUDE_DIRECTORIES} 
    ${Boost_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

SET(MY_SRCS  
    #src/alg_string.cpp
    #src/cast.cpp
    #src/base.cpp
    #src/class.cpp
    #src/boost1.cpp
    src/smartptr.cpp
    #/test.cxx
)

ADD_EXECUTABLE(boost_example ${MY_SRCS})
target_link_libraries(boost_example boost_program_options boost_system boost_thread
     boost_regex)
