cmake_minimum_required(VERSION 2.6)
 
Project(cpp_example)
#SET(CMAKE_CXX_COMPILER "g++-4.9")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lboost_program_options -lboost_system -lboost_thread -lboost_timer -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")
#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
#FIND_PACKAGE(Boost)
#set(Boost_USE_MULTITHREADED ON) # which is the default
FIND_PACKAGE(Boost COMPONENTS program_options required )
#find_package(Threads)
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
    #boost_src/alg_string.cpp
    #boost_src/cast.cpp
    #boost_src/base.cpp
    #boost_src/boost1.cpp
    #boost_src/smartptr.cpp
    #boost_src/asio.cpp
    
    #cppProLan/base.cpp
    #cppProLan/lan.cpp
    #cppProLan/cast.cpp
    cppProLan/class.cpp
    #cppProLan/algorithm.cpp
    #cppProLan/contain.cpp
    #cppProLan/stl.cpp
    #cppProLan/thread.cpp
    #cppProLan/utility.cpp
    #cppProLan/regex.cpp

)

ADD_EXECUTABLE(cpp_example ${MY_SRCS})
target_link_libraries(cpp_example 
    ${CMAKE_THREAD_LIBS_INIT}
    #boost_program_options
    #boost_regex
    boost_system
    boost_thread
    boost_timer
    )
#target_link_libraries (cpp_example ${CMAKE_THREAD_LIBS_INIT})
