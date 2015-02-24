#include "Matrix.h"
#include "MatrixTest.h"

#include <iostream>
#include <cppunit/ui/text/TestRunner.h>

template< typename T >
void print( const Matrix< T >& matrix );



int main( int argc, const char* argv[ ] )
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( MatrixTest::suite() );
  runner.run();
  
  return 0;
}



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
