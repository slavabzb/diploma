#include "MatrixTest.h"

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "HelperClasses/Logger.h"
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
  Logger::getInstance()->write( "\nTime test started." );
  
  TimeStatistics additionStatistics;
  TimeStatistics multiplicationStatistics;
  TimeStatistics transpositionStatistics;
  
  const std::size_t initialSize = 10;
  const std::size_t sizeStep = 2;
  const std::size_t nIterations = 4;
  
  Logger::getInstance()->write( "\nInitial size: " )
    ->write( initialSize )
    ->write( "\nSize step: " )
    ->write( sizeStep )
    ->write( " x Current size" )
    ->write( "\nTotal iterations: " )
    ->write( nIterations )
    ->write( "\n\n" );
  
  std::size_t size = initialSize;
  for( std::size_t iteration = 0; iteration < nIterations; ++iteration ) {
    Logger::getInstance()->write( "[" )
      ->write( iteration / static_cast< float >( nIterations ) * 100 )
      ->write( "%] Size = " )
      ->write( size  )
      ->write( "\n" );
    
    Logger::getInstance()->write( "\tFilling lhs...                " );
    matrix_t lhs( size, size );
    this->timeMeasurer.start();
    this->matrixRandomFiller.fill( lhs );
    this->timeMeasurer.end();
    Logger::getInstance()->write( "ok\t(" )
      ->write( this->timeMeasurer.getDurationInSeconds() )
      ->write( "s)\n" );
    
    Logger::getInstance()->write( "\tFilling rhs...                " );
    matrix_t rhs( size, size );
    this->timeMeasurer.start();
    this->matrixRandomFiller.fill( rhs );
    this->timeMeasurer.end();
    Logger::getInstance()->write( "ok\t(" )
      ->write( this->timeMeasurer.getDurationInSeconds() )
      ->write( "s)\n" );

    matrix_t result( size, size );
    
    Logger::getInstance()->write( "\tOut-of-class summarizing...   " );
    this->timeMeasurer.start();
    this->matrixSummarizer.summarize( result, lhs, rhs );
    this->timeMeasurer.end();
    additionStatistics[ size ].singleTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( "ok\t(" )
      ->write( this->timeMeasurer.getDurationInSeconds() )
      ->write( "s)\n" );
    
    Logger::getInstance()->write( "\tIn-class summarizing...       " );
    this->timeMeasurer.start();
    lhs + rhs;
    this->timeMeasurer.end();
    additionStatistics[ size ].multyTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( "ok\t(" )
      ->write( this->timeMeasurer.getDurationInSeconds() )
      ->write( "s)\n" );

    Logger::getInstance()->write( "\tOut-of-class transposition... " );
    this->timeMeasurer.start();
    this->matrixTransposer.transpose( result, lhs );
    this->timeMeasurer.end();
    transpositionStatistics[ size ].singleTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( "ok\t(" )
      ->write( this->timeMeasurer.getDurationInSeconds() )
      ->write( "s)\n" );
    
    Logger::getInstance()->write( "\tIn-class transposition...     " );
    this->timeMeasurer.start();
    lhs.transpose();
    this->timeMeasurer.end();
    transpositionStatistics[ size ].multyTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( "ok\t(" )
      ->write( this->timeMeasurer.getDurationInSeconds() )
      ->write( "s)\n" );
    
    Logger::getInstance()->write( "\tOut-of-class multiplying...   " );
    this->timeMeasurer.start();
    this->matrixMultiplier.multiply( result, lhs, rhs );
    this->timeMeasurer.end();
    multiplicationStatistics[ size ].singleTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( "ok\t(" )
      ->write( this->timeMeasurer.getDurationInSeconds() )
      ->write( "s)\n" );
    
    Logger::getInstance()->write( "\tIn-class multiplying...       " );
    this->timeMeasurer.start();
    lhs * rhs;
    this->timeMeasurer.end();
    multiplicationStatistics[ size ].multyTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( "ok\t(" )
      ->write( this->timeMeasurer.getDurationInSeconds() )
      ->write( "s)\n" );
    
    size += size * sizeStep;
  }
  
  TimeStatisticsPrinter printer;
  printer.print( "Addition", additionStatistics );
  printer.print( "Multiplication", multiplicationStatistics );
  printer.print( "Transposition", transpositionStatistics );
  
  printer.save( "statistics" );
}



