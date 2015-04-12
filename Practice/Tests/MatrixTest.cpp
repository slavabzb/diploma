#include "MatrixTest.h"

#include <valarray>

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "HelperClasses/Logger.h"
#include "HelperClasses/MatrixPrinter.h"
#include "HelperClasses/Statistics.h"



CPPUNIT_TEST_SUITE_REGISTRATION( MatrixTest );



void MatrixTest::testCrashDoubleType()
{
  MatrixRandomFiller filler;
  MatrixMultiplier multiplier;
  MatrixPrinter printer( &std::cout );
  printer.setPrecision( 20 );
  
  std::size_t nRows = 2;
  std::size_t nColumns = 2;
  
  Matrix< double > matrix_a( nRows, nColumns );
  Matrix< double > matrix_b( nRows, nColumns );
  
  filler.fill( matrix_a );
  filler.fill( matrix_b );
  
  printer.print( matrix_a );
  printer.print( matrix_b );
  
  Matrix< double > matrix_c( nRows, nColumns );
  multiplier.multiply( matrix_c, matrix_a, matrix_b );
  
  Matrix< double > matrix_d( nRows, nColumns );
  matrix_d = matrix_a * matrix_b;
  
  printer.print( matrix_c );
  printer.print( matrix_d );
}



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
  matrix_t matrix( this->matrixSize, 2 * this->matrixSize );
  this->matrixRandomFiller.fill( matrix );
  
  matrix_t matrix_copy = matrix;

  matrix_t matrix_transp( matrix.get_columns(), matrix.get_rows() );
  this->matrixTransposer.transpose( matrix_transp, matrix );

  matrix.transpose();
  
  CPPUNIT_ASSERT( matrix == matrix_transp );
  
  const std::size_t row = 4;
  const std::size_t column = 5;
  
  CPPUNIT_ASSERT( matrix_copy( row, column ) == matrix( column, row ) );
  
  matrix.transpose();
  
  CPPUNIT_ASSERT( matrix == matrix_copy );
  CPPUNIT_ASSERT( matrix( row, column ) == matrix_copy( row, column ) );
}



void MatrixTest::testTime()
{
  Logger::getInstance()->write( "\nTime test started." );
  
  const std::size_t initialSize = 10;
  const std::size_t sizeStep = 1;
  const std::size_t nIterations = 4;
  const std::size_t nInnerLoopIterations = 10;
    
  Logger::getInstance()->write( "\nInitial size: " )
    ->write( initialSize )
    ->write( "\nSize step: " )
    ->write( sizeStep )
    ->write( " x Current size" )
    ->write( "\nTotal iterations: " )
    ->write( nIterations )
    ->write( "\n" )
    ->write( "In-loop iterations number: " )
    ->write( nInnerLoopIterations )
    ->write( "\n\n" );
  
  Statistics statistics;
  
  std::size_t size = initialSize;
  for( std::size_t iteration = 0; iteration < nIterations; ++iteration ) {
    std::valarray< double > durations( nInnerLoopIterations );
    
    Logger::getInstance()->write( "[" )
      ->write( 100.0 * iteration / ( nIterations - 1 ) )
      ->write( "%] The size of the matrices is " )
      ->write( size  )
      ->write( ".\n" );
    
    Logger::getInstance()->write( "\tFilling lhs...                " );
    matrix_t lhs( size, size );
    this->timeMeasurer.start();
    this->matrixRandomFiller.fill( lhs );
    this->timeMeasurer.end();
    Logger::getInstance()->write( "          ok\t" )
      ->write( this->timeMeasurer.getDurationInSeconds() )
      ->write( "s\n" );
    
    Logger::getInstance()->write( "\tFilling rhs...                " );
    matrix_t rhs( size, size );
    this->timeMeasurer.start();
    this->matrixRandomFiller.fill( rhs );
    this->timeMeasurer.end();
    Logger::getInstance()->write( "          ok\t" )
      ->write( this->timeMeasurer.getDurationInSeconds() )
      ->write( "s\n" );

    matrix_t result( size, size );
    
    Logger::getInstance()->write( "\tOut-of-class summarizing...   [       ]" );
    for( std::size_t iDuration = 0; iDuration < durations.size(); ++iDuration ) {
      this->timeMeasurer.start();
      this->matrixSummarizer.summarize( result, lhs, rhs );
      this->timeMeasurer.end();
      durations[ iDuration ] = this->timeMeasurer.getDurationInSeconds();
      Logger::getInstance()->write( "\b\b\b\b\b\b\b\b" )
        ->write( 100.0 * iDuration / ( durations.size() - 1 ) )
        ->write( "%]" );
    }
    statistics( size, Statistics::Addition ).setSingleThreadTime( durations.sum() / durations.size() );
    Logger::getInstance()->write( " ok\t" )
      ->write( statistics( size, Statistics::Addition ).getSingleThreadTime() )
      ->write( "s\n" );
    
    Logger::getInstance()->write( "\tIn-class summarizing...       [       ]" );
    for( std::size_t iDuration = 0; iDuration < durations.size(); ++iDuration ) {
      this->timeMeasurer.start();
      lhs + rhs;
      this->timeMeasurer.end();
      durations[ iDuration ] = this->timeMeasurer.getDurationInSeconds();
      Logger::getInstance()->write( "\b\b\b\b\b\b\b\b" )
        ->write( 100.0 * iDuration / ( durations.size() - 1 ) )
        ->write( "%]" );
    }
    statistics( size, Statistics::Addition ).setMultyThreadTime( durations.sum() / durations.size() );
    Logger::getInstance()->write( " ok\t" )
      ->write( statistics( size, Statistics::Addition ).getMultyThreadTime() )
      ->write( "s\n" );
    
    Logger::getInstance()->write( "\tOut-of-class multiplying...   [       ]" );
    for( std::size_t iDuration = 0; iDuration < durations.size(); ++iDuration ) {
      this->timeMeasurer.start();
      this->matrixMultiplier.multiply( result, lhs, rhs );
      this->timeMeasurer.end();
      durations[ iDuration ] = this->timeMeasurer.getDurationInSeconds();
      Logger::getInstance()->write( "\b\b\b\b\b\b\b\b" )
        ->write( 100.0 * iDuration / ( durations.size() - 1 ) )
        ->write( "%]" );
    }
    statistics( size, Statistics::Multiplication ).setSingleThreadTime( durations.sum() / durations.size() );
    Logger::getInstance()->write( " ok\t" )
      ->write( statistics( size, Statistics::Multiplication ).getSingleThreadTime() )
      ->write( "s\n" );
    
    Logger::getInstance()->write( "\tIn-class multiplying...       [       ]" );
    for( std::size_t iDuration = 0; iDuration < durations.size(); ++iDuration ) {
      this->timeMeasurer.start();
      lhs * rhs;
      this->timeMeasurer.end();
      durations[ iDuration ] = this->timeMeasurer.getDurationInSeconds();
      Logger::getInstance()->write( "\b\b\b\b\b\b\b\b" )
        ->write( 100.0 * iDuration / ( durations.size() - 1 ) )
        ->write( "%]" );
    }
    statistics( size, Statistics::Multiplication ).setMultyThreadTime( durations.sum() / durations.size() );
    Logger::getInstance()->write( " ok\t" )
      ->write( statistics( size, Statistics::Multiplication ).getMultyThreadTime() )
      ->write( "s\n" );
        
    size += size * sizeStep;
  }
  
  const std::string fileName = "statistics";
  statistics.save( fileName );
}



