#include "MatrixTest.h"

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "HelperClasses/Statistics.h"



CPPUNIT_TEST_SUITE_REGISTRATION( MatrixTest );



void MatrixTest::testAddition()
{  
  matrix_t A( this->matrixSize, this->matrixSize );
  this->matrixRandomFiller.fill( A );

  matrix_t B( this->matrixSize, this->matrixSize );
  this->matrixRandomFiller.fill( B );

  matrix_t C( this->matrixSize, this->matrixSize );
  this->matrixSummarizer.summarize( C, A, B );

  matrix_t D( A + B );

  CPPUNIT_ASSERT( C == D );
}



void MatrixTest::testMultiplication()
{
  matrix_t A( this->matrixSize, this->matrixSize );
  this->matrixRandomFiller.fill( A );

  matrix_t B( this->matrixSize, this->matrixSize );
  this->matrixRandomFiller.fill( B );

  matrix_t C( this->matrixSize, this->matrixSize );
  this->matrixMultiplier.multiply( C, A, B );

  matrix_t D( A * B );

  CPPUNIT_ASSERT( C == D );
  
  matrix_t E( A );
  element_t value = 2;
  this->matrixMultiplier.multiply( value, E );

  matrix_t F( value * A );

  CPPUNIT_ASSERT( A == E );
}



void MatrixTest::testTransposition()
{
  matrix_t A( this->matrixSize, this->matrixSize );
  this->matrixRandomFiller.fill( A );

  matrix_t B( this->matrixSize, this->matrixSize );
  this->matrixTransposer.transpose( B, A );

  matrix_t C( A.transpose() );
  
  CPPUNIT_ASSERT( B == C );
}



void MatrixTest::testTime()
{
  TimeStatistics additionStatistics;
  TimeStatistics multiplicationStatistics;
  TimeStatistics transpositionStatistics;
  
  const std::size_t initialSize = 10;
  const std::size_t sizeStep = 5;
  const std::size_t nIterations = 5;
    
  std::size_t size = initialSize;
  for( std::size_t iteration = 0; iteration < nIterations; ++iteration ) {
    matrix_t lhs( size, size );
    this->matrixRandomFiller.fill( lhs );

    matrix_t rhs( size, size );
    this->matrixRandomFiller.fill( rhs );

    matrix_t result( size, size );
    
    this->timeMeasurer.start();
    this->matrixSummarizer.summarize( result, lhs, rhs );
    this->timeMeasurer.end();
    additionStatistics[ size ].singleTime = this->timeMeasurer.getDurationInSeconds();
    
    this->timeMeasurer.start();
    lhs + rhs;
    this->timeMeasurer.end();
    additionStatistics[ size ].multyTime = this->timeMeasurer.getDurationInSeconds();

    this->timeMeasurer.start();
    this->matrixTransposer.transpose( result, lhs );
    this->timeMeasurer.end();
    transpositionStatistics[ size ].singleTime = this->timeMeasurer.getDurationInSeconds();
    
    this->timeMeasurer.start();
    lhs.transpose();
    this->timeMeasurer.end();
    transpositionStatistics[ size ].multyTime = this->timeMeasurer.getDurationInSeconds();
    
    this->timeMeasurer.start();
    this->matrixMultiplier.multiply( result, lhs, rhs );
    this->timeMeasurer.end();
    multiplicationStatistics[ size ].singleTime = this->timeMeasurer.getDurationInSeconds();
    
    this->timeMeasurer.start();
    lhs * rhs;
    this->timeMeasurer.end();
    multiplicationStatistics[ size ].multyTime = this->timeMeasurer.getDurationInSeconds();
    
    size += sizeStep;
  }
  
  TimeStatisticsPrinter printer;
  printer.print( "Addition", additionStatistics );
  printer.print( "Multiplication", multiplicationStatistics );
  printer.print( "Transposition", transpositionStatistics );
  
  printer.save( "statistics" );
}



