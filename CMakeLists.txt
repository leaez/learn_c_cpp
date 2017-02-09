cmake_minimum_required(VERSION 2.6)
 
Project(boost_example)
#SET(CMAKE_CXX_COMPILER "g++-4.9")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
FIND_PACKAGE(Boost)
#set(Boost_USE_MULTITHREADED ON) # which is the default
#FIND_PACKAGE(Boost COMPONENTS program_options required )
find_package(Threads)
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
    #src/smartptr.cpp
    #/test.cxx

    #cppProLan/base.cpp
    #cppProLan/cast.cpp
    #cppProLan/contain.cpp
    #cppProLan/stl.cpp
    #cppProLan/thread.cpp
    #cppProLan/algorithm.cpp
    #cppProLan/regex.cpp
    cppProLan/lan.cpp

    #cppProLan/utility.cpp
)

ADD_EXECUTABLE(boost_example ${MY_SRCS})
target_link_libraries(boost_example boost_program_options
    ${CMAKE_THREAD_LIBS_INIT}
    boost_program_options
    #boost_regex
    boost_system
    #boost_thread
    )
#target_link_libraries (boost_example ${CMAKE_THREAD_LIBS_INIT})
