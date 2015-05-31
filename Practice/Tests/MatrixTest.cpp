#include "MatrixTest.h"

#include <valarray>

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "HelperClasses/MatrixPrinter.h"
#include "HelperClasses/Statistics.h"

#include "HelperClasses/MatrixSummarizer.h"
#include "HelperClasses/MatrixMultiplier.h"



CPPUNIT_TEST_SUITE_REGISTRATION( MatrixTest );



void MatrixTest::crash_double_type()
{
  std::size_t rows = 2;
  std::size_t columns = 2;
  
  Matrix< double > A( rows, columns );
  Matrix< double > B( rows, columns );
  
  MatrixRandomFiller matrix_random_filler;
  matrix_random_filler.fill( A );
  matrix_random_filler.fill( B );
  
  MatrixPrinter matrix_printer( &std::cout );
  matrix_printer.set_precision( 20 );
  matrix_printer.print( A );
  matrix_printer.print( B );
  
  Matrix< double > C( rows, columns );
  MatrixMultiplier matrix_multiplier;
  matrix_multiplier.multiply( C, A, B );
  
  Matrix< double > D( rows, columns );
  D = A * B;
  
  matrix_printer.print( C );
  matrix_printer.print( D );
}



void MatrixTest::addition()
{  
  matrix_t A( this->matrix_size, this->matrix_size );
  this->matrix_random_filler.fill( A );

  matrix_t B( this->matrix_size, this->matrix_size );
  this->matrix_random_filler.fill( B );

  matrix_t C( this->matrix_size, this->matrix_size );
  MatrixSummarizer matrix_summarizer;
  matrix_summarizer.summarize( C, A, B );

  matrix_t D = ( B + A );

  CPPUNIT_ASSERT( C == D );
}



void MatrixTest::multiplication()
{
  matrix_t A( this->matrix_size, this->matrix_size );
  this->matrix_random_filler.fill( A );

  matrix_t B( this->matrix_size, this->matrix_size );
  this->matrix_random_filler.fill( B );

  matrix_t C( this->matrix_size, this->matrix_size );
  MatrixMultiplier matrix_multiplier;
  matrix_multiplier.multiply( C, A, B );

  matrix_t D = ( A * B );

  CPPUNIT_ASSERT( C == D );
  
  matrix_t E = A;
  value_t value = 2;
  matrix_multiplier.multiply( value, E );

  matrix_t F( A * value );

  CPPUNIT_ASSERT( F == E );
}



void MatrixTest::transposition()
{ 
  matrix_t matrix( 2, 3 );
  this->matrix_random_filler.fill( matrix );
  
  matrix_t matrix_transposed = matrix.transpose();

  for( std::size_t iRow = 0; iRow < matrix.get_rows(); ++iRow ) {
    for( std::size_t jColumn = 0; jColumn < matrix.get_columns(); ++jColumn ) {
      CPPUNIT_ASSERT( matrix( iRow, jColumn ) == matrix_transposed( jColumn, iRow ) );
    }
  }
}



void MatrixTest::acceleration()
{
  std::size_t size = this->initial_size;
  for( std::size_t iteration = 0; iteration < iterations_num; ++iteration ) {    
    matrix_t lhs( size, size );
    this->matrix_random_filler.fill( lhs );
    
    matrix_t rhs( size, size );
    this->matrix_random_filler.fill( rhs );

    matrix_t result( size, size );
    
    auto single_thread_summarizing = [ & ]() {
      std::size_t nthreads = 1;
      matrix_t::get_parallel_handler()->set_direct_parallel_policy( nthreads );
      result = ( lhs + rhs );
    };
    
    auto multiple_thread_summarizing = [ & ]() {
      matrix_t::get_parallel_handler()->set_auto_parallel_policy();
      result = ( lhs + rhs );
    };
    
    auto single_thread_multiplication = [ & ]() {
      std::size_t nthreads = 1;
      matrix_t::get_parallel_handler()->set_direct_parallel_policy( nthreads );
      result = ( lhs * rhs );
    };
    
    auto multiple_thread_multiplication = [ & ]() {
      matrix_t::get_parallel_handler()->set_auto_parallel_policy();
      result = ( lhs * rhs );
    };
    
    this->statistics( size, Statistics::Addition ).set_single_thread_time(
      this->calculate_average_time( single_thread_summarizing )
    );

    this->statistics( size, Statistics::Addition ).set_multiple_threads_time(
      this->calculate_average_time( multiple_thread_summarizing )
    );

    this->statistics( size, Statistics::Multiplication ).set_single_thread_time(
      this->calculate_average_time( single_thread_multiplication )
    );

    this->statistics( size, Statistics::Multiplication ).set_multiple_threads_time(
      this->calculate_average_time( multiple_thread_multiplication )
    );

    size = this->initial_size * (this->size_step + 10 * iteration);
  }
  
  const std::string file = "Acceleration statistics";
  this->statistics.save( file );
}



void MatrixTest::multiple_threads_time()
{
  this->inner_loop_iterations_num = 1;
  this->initial_size = 500;
  this->size_step = 500;
  this->iterations_num = 0;
  
  std::size_t size = this->initial_size;
  for( std::size_t iteration = 0; iteration < this->iterations_num; ++iteration ) {    
    matrix_t lhs( size, size );
    this->matrix_random_filler.fill( lhs );
    
    matrix_t rhs( size, size );
    this->matrix_random_filler.fill( rhs );

    matrix_t multiple_thread_result( size, size );
        
    auto multiple_thread_summarizing = [ & ]() {
      multiple_thread_result = ( lhs + rhs );
    };

    auto multiple_thread_multiplication = [ & ]() {
      multiple_thread_result = ( lhs * rhs );
    };
    
    this->statistics( size, Statistics::Addition ).set_multiple_threads_time(
      this->calculate_average_time( multiple_thread_summarizing )
    );

    this->statistics( size, Statistics::Multiplication ).set_multiple_threads_time(
      this->calculate_average_time( multiple_thread_multiplication )
    );

    size += this->size_step;
  }
  
  const std::string file = "Multithreading statistics";
  this->statistics.save( file );
}



void MatrixTest::threads_number_time()
{
  const std::size_t matrix_size = 500;
  this->inner_loop_iterations_num = 0;

  matrix_t lhs( matrix_size, matrix_size );
  this->matrix_random_filler.fill( lhs );

  matrix_t rhs( matrix_size, matrix_size );
  this->matrix_random_filler.fill( rhs );

  matrix_t result( matrix_size, matrix_size );

  auto multiple_thread_multiplication = [ & ]() {
    result = ( lhs * rhs );
  };

  double time = this->calculate_average_time( multiple_thread_multiplication );
  
  const std::string file = "Time (using 2 threads)";
  std::ofstream fstream( file );
  
  fstream << time;
}



void MatrixTest::matrix_types()
{
  Matrix< int > E( 3, 3 );
  E( 0, 0 ) = 1;
  E( 1, 1 ) = 1;
  E( 2, 2 ) = 1;
  CPPUNIT_ASSERT( E == Matrix< int >::Type::identity( 3 ) );
}



