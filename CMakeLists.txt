cmake_minimum_required(VERSION 2.6)
 
Project(cpplan)
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
    cpp_example/cppProLan/base.cpp
    #cpp_example/cppProLan/lan.cpp
    #cpp_example/cppProLan/cast.cpp
    #cpp_example/cppProLan/class.cpp
    #cpp_example/cppProLan/algorithm.cpp
    #cpp_example/cppProLan/contain.cpp
    #cpp_example/cppProLan/stl.cpp
    #cpp_example/cppProLan/thread.cpp
    #cpp_example/cppProLan/utility.cpp
    #cpp_example/cppProLan/regex.cpp
    
    #cpp_example/boost_src/alg_string.cpp
    #cpp_example/boost_src/cast.cpp
    #cpp_example/boost_src/base.cpp
    #cpp_example/boost_src/boost1.cpp
    #cpp_example/boost_src/smartptr.cpp
    #cpp_example/boost_src/asio.cpp

)

ADD_EXECUTABLE(cpplan ${MY_SRCS})
target_link_libraries(cpplan boost_program_options
    ${CMAKE_THREAD_LIBS_INIT}
    boost_program_options
    #boost_regex
    boost_system
    #boost_thread
    )
#target_link_libraries (cpplan ${CMAKE_THREAD_LIBS_INIT})
