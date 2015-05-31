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
  matrix_c = multiplier.multiply( matrix_a, matrix_b );
  
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
  C = this->matrixSummarizer.summarize( A, B );

  matrix_t D( B + A );

  CPPUNIT_ASSERT( C == D );
}



void MatrixTest::testMultiplication()
{
  matrix_t A( this->matrixSize, this->matrixSize );
  this->matrixRandomFiller.fill( A );

  matrix_t B( this->matrixSize, this->matrixSize );
  this->matrixRandomFiller.fill( B );

  matrix_t C( this->matrixSize, this->matrixSize );
  C = this->matrixMultiplier.multiply( A, B );

  matrix_t D = ( A * B );

  CPPUNIT_ASSERT( C == D );
  
  matrix_t E = A;
  element_t value = 2;
  this->matrixMultiplier.multiply( value, E );

  matrix_t F( A * value );

  CPPUNIT_ASSERT( F == E );
}



void MatrixTest::testTransposition()
{ 
  matrix_t matrix( 2, 3 );
  this->matrixRandomFiller.fill( matrix );
  
  matrix_t matrix_transposed = matrix.transpose();

  for( std::size_t iRow = 0; iRow < matrix.get_rows(); ++iRow ) {
    for( std::size_t jColumn = 0; jColumn < matrix.get_columns(); ++jColumn ) {
      CPPUNIT_ASSERT( matrix( iRow, jColumn ) == matrix_transposed( jColumn, iRow ) );
    }
  }
}



void MatrixTest::testAcceleration()
{
  std::size_t size = this->initialSize;
  for( std::size_t iteration = 0; iteration < nIterations; ++iteration ) {    
    matrix_t lhs( size, size );
    this->matrixRandomFiller.fill( lhs );
    
    matrix_t rhs( size, size );
    this->matrixRandomFiller.fill( rhs );

    matrix_t single_thread_result( size, size );
    matrix_t multiple_thread_result( size, size );
    
    auto single_thread_summarizing = [ & ]() {
      single_thread_result = this->matrixSummarizer.summarize( lhs, rhs );
    };
    
    auto multiple_thread_summarizing = [ & ]() {
      multiple_thread_result = ( lhs + rhs );
    };
    
    auto single_thread_multiplication = [ & ]() {
      single_thread_result = this->matrixMultiplier.multiply( lhs, rhs );
    };
    
    auto multiple_thread_multiplication = [ & ]() {
      multiple_thread_result = ( lhs * rhs );
    };
    
    this->statistics( size, Statistics::Addition ).setSingleThreadTime(
      this->calculateAverageTime( single_thread_summarizing )
    );

    this->statistics( size, Statistics::Addition ).setMultyThreadTime(
      this->calculateAverageTime( multiple_thread_summarizing )
    );

    this->statistics( size, Statistics::Multiplication ).setSingleThreadTime(
      this->calculateAverageTime( single_thread_multiplication )
    );

    this->statistics( size, Statistics::Multiplication ).setMultyThreadTime(
      this->calculateAverageTime( multiple_thread_multiplication )
    );

    size = this->initialSize * (this->sizeStep + 10 * iteration);
  }
  
  const std::string fileName = "Acceleration statistics";
  this->statistics.save( fileName );
}



void MatrixTest::testMultithreadingTime()
{
  this->nInnerLoopIterations = 1;
  this->initialSize = 500;
  this->sizeStep = 500;
  this->nIterations = 0;
  
  std::size_t size = this->initialSize;
  for( std::size_t iteration = 0; iteration < this->nIterations; ++iteration ) {    
    matrix_t lhs( size, size );
    this->matrixRandomFiller.fill( lhs );
    
    matrix_t rhs( size, size );
    this->matrixRandomFiller.fill( rhs );

    matrix_t multiple_thread_result( size, size );
        
    auto multiple_thread_summarizing = [ & ]() {
      multiple_thread_result = ( lhs + rhs );
    };

    auto multiple_thread_multiplication = [ & ]() {
      multiple_thread_result = ( lhs * rhs );
    };
    
    this->statistics( size, Statistics::Addition ).setMultyThreadTime(
      this->calculateAverageTime( multiple_thread_summarizing )
    );

    this->statistics( size, Statistics::Multiplication ).setMultyThreadTime(
      this->calculateAverageTime( multiple_thread_multiplication )
    );

    size += this->sizeStep;
  }
  
  const std::string fileName = "Multithreading statistics";
  this->statistics.save( fileName );
}



void MatrixTest::testThreadsNumberTime()
{
  const std::size_t matrixSize = 500;
  this->nInnerLoopIterations = 0;

  matrix_t lhs( matrixSize, matrixSize );
  this->matrixRandomFiller.fill( lhs );

  matrix_t rhs( matrixSize, matrixSize );
  this->matrixRandomFiller.fill( rhs );

  matrix_t result( matrixSize, matrixSize );

  auto multiple_thread_multiplication = [ & ]() {
    result = ( lhs * rhs );
  };

  double time = this->calculateAverageTime( multiple_thread_multiplication );
  
  const std::string fileName = "Time (using 2 threads)";
  std::ofstream fstream( fileName );
  
  fstream << time;
}



void MatrixTest::testMatrixTypes()
{
  Matrix< int > E( 3, 3 );
  E( 0, 0 ) = 1;
  E( 1, 1 ) = 1;
  E( 2, 2 ) = 1;
  CPPUNIT_ASSERT( E == Matrix< int >::Type::Identity( 3 ) );
}



