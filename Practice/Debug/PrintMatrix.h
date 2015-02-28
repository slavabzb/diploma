#include <iostream>

#include "Matrix.h"



template< typename T >
void print( const Matrix< T >& matrix )
{
  for ( auto iRow = 0; iRow < matrix.get_rows(); ++iRow ) {
    for ( auto iColumn = 0; iColumn < matrix.get_columns(); ++iColumn ) {
      std::cout << matrix( iRow, iColumn ) << ' ';
    }
    std::cout << '\n';
  }
}
