#include "Matrix.h"
#include "ConstructionTest.h"

int main( int argc, const char* argv[ ] )
{
  Matrix< float > m1( 2, 3 );
  Matrix< float > m2( m1 );
  
  return 0;
}
