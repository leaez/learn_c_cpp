cmake_minimum_required(VERSION 2.8)
 
Project(cpp_example)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
#find_package(Threads)
LINK_DIRECTORIES(
    ${LINK_DIRECTORIES} 
    
)

INCLUDE_DIRECTORIES(
    ${INCLUDE_DIRECTORIES} 
    ${PROJECT_SOURCE_DIR}/include
)

SET(MY_SRCS
  cLan/clib.c

)

ADD_EXECUTABLE(cLan ${MY_SRCS})
target_link_libraries(cLan 
    ${CMAKE_THREAD_LIBS_INIT}
    )
#target_link_libraries (cpp_example ${CMAKE_THREAD_LIBS_INIT})
