#include "ConstructionTest.h"
#include "Matrix.h"

ConstructionTest::ConstructionTest( const std::string& testName )
  : CppUnit::TestCase( testName )
{

}



void ConstructionTest::runTest()
{
  Matrix< int32_t > m0( 2, 3, 4 );
  Matrix< int32_t > m1 = m0;  
  CPPUNIT_ASSERT( m0 == m1 );

  Matrix< float > m2( 5, 6 );
  Matrix< float > m3( 6, 5 );
  CPPUNIT_ASSERT( m2 != m3 );

  Matrix< double > m4( 4, 5, 1 );
  Matrix< double > m5( 3, 2, 5);
  Matrix< double > m6( std::move( m5 ) );
  CPPUNIT_ASSERT( (m4 != m6) && !(m6 == m4) );
}
