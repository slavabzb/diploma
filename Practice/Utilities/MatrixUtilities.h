#ifndef MATRIX_UTILITIES
#define MATRIX_UTILITIES

#include <iostream>
#include <chrono>
#include <random>
#include <thread>

#include "Matrix.h"



template< typename T >
void fillMatrixWithRandom( Matrix< T >& matrix )
{
  uint64_t seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator( seed );
  std::uniform_real_distribution<> distribution( 0, 1 );
  
  for( std::size_t iRow = 0; iRow < matrix.get_rows(); ++iRow ) {
    for( std::size_t jColumn = 0; jColumn < matrix.get_columns(); ++jColumn ) {
      matrix( iRow, jColumn ) = distribution( generator );
    }
  }
}



template< typename T >
void multiplyMatrices( Matrix< T >& result, const Matrix< T >& lhs, const Matrix< T >& rhs )
{
  assert( lhs.get_columns() == rhs.get_rows() );
  assert( result.get_rows() == lhs.get_rows() );
  assert( result.get_columns() == rhs.get_columns() );
  
  auto calculateBlock = [ &result, &rhs, &lhs ]( std::size_t iRowStart, std::size_t iRowEnd ) -> void
  {
    for( std::size_t iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
      for( std::size_t jColumn = 0; jColumn < rhs.get_columns(); ++jColumn ) {
        double sum = 0.0;
        for( std::size_t kIndex = 0; kIndex < lhs.get_columns(); ++kIndex ) {
          sum += lhs( iRow, kIndex ) * rhs( kIndex, jColumn );
        }
        result( iRow, jColumn ) = sum;
      }
    }
  };
  
  const std::size_t nRows = lhs.get_rows();
  
  std::thread thread( calculateBlock, 0, nRows / 2 );
  
  calculateBlock( nRows / 2, nRows );
  
  thread.join();
}



template< typename T >
void printMatrix( const Matrix< T >& matrix )
{
  std::cout.precision( 20 );
  std::cout << '\n';
  for ( std::size_t iRow = 0; iRow < matrix.get_rows(); ++iRow ) {
    for ( std::size_t iColumn = 0; iColumn < matrix.get_columns(); ++iColumn ) {
      std::cout << std::fixed << matrix( iRow, iColumn ) << ' ';
    }
    std::cout << '\n';
  }
}



#endif // MATRIX_UTILITIES
