cmake_minimum_required( VERSION 2.8 )

set( PROJECT MatrixTester )

project( ${PROJECT} )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread" )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( SOURCE
  main.cpp
  ParallelHandler.cpp
  Tests/MatrixTest.cpp
  HelperClasses/Logger.cpp
  HelperClasses/MatrixPrinter.cpp
  HelperClasses/Statistics.cpp
  HelperClasses/TimeMeasurer.cpp
)

option( TIME_TEST "Enable time test specific definitions" OFF )

if( TIME_TEST )
  add_definitions( -DTIME_TEST )
endif( TIME_TEST)

add_executable( ${PROJECT} ${SOURCE} )

target_link_libraries( ${PROJECT} cppunit )
target_link_libraries( ${PROJECT} gmpxx )
target_link_libraries( ${PROJECT} gmp )
