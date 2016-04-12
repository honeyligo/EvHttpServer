CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_C_COMPILER "gcc")
  
PROJECT(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
SET(LIBS event event_pthreads)
SET(TARGET_NAME test)

#TARGET_TYPE
#LIBRARY | ARCHIVE | RUNTIME
#¶¯Ì¬¿â  | ¾²Ì¬¿â  | ¿ÉÖ´ÐÐ

SET(TARGET_TYPE RUNTIME)
SET(SRC_LIST evhttpserver/EvHttpServer.cpp
			evhttpserver/EvHttpThread.cpp
			MMDCHttpServer.cpp
			main.cpp)
SET(USTD_LIST ustd/thread.cpp)

INCLUDE_DIRECTORIES(.
					ustd)

ADD_EXECUTABLE(test ${SRC_LIST} ${USTD_LIST})	
TARGET_LINK_LIBRARIES (test ${LIBS})
