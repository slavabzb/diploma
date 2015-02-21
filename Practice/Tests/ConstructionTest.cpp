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
}
