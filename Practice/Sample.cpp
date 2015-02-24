#include "Matrix.h"
#include "ConstructionTest.h"

int main( int argc, const char* argv[ ] )
{
  ConstructionTest test( "Construction test" );
  //test.runTest();
  
  Matrix< int > m( 2, 3, 4 );
  m( 0, 0 ) = 1;
  m( 1, 2 ) = 2;
  
  return 0;
}
