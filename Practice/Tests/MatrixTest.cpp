#include "MatrixTest.h"

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

void MatrixTest::setUp()
{

}

void MatrixTest::tearDown()
{

}

void MatrixTest::testConstruction()
{
  Matrix< int32_t > m0( 5, 6 );
  Matrix< int32_t > m1( 6, 5 );
  Matrix< int32_t > m2( m1 );
  Matrix< int32_t > m3( Matrix< int32_t >( 3, 4, 5 ) );
  
  CPPUNIT_ASSERT( m0 != m1 );
  CPPUNIT_ASSERT( m2 == m1 );
  CPPUNIT_ASSERT( m3 == Matrix< int32_t >( 3, 4, 5 ) );
}

void MatrixTest::testAccessing()
{
  Matrix< int32_t > m0( 3, 4, 5 );
  Matrix< int32_t > m1( 2, 3, 4 );
  
  m0( 0, 0 ) = 1;
  m1( 1, 2 ) = 1;
  
  CPPUNIT_ASSERT( m0( 0, 0 ) == m1( 1, 2 ) );
  CPPUNIT_ASSERT( m0( 1, 3 ) != m1( 0, 2 ) );
}

CppUnit::Test* MatrixTest::suite()
{
  auto suite = new CppUnit::TestSuite( "MatrixTest" );
  
  suite->addTest(
    new CppUnit::TestCaller< MatrixTest > (
      "testConstruction",
      &MatrixTest::testConstruction
    )
  );
  
  suite->addTest(
    new CppUnit::TestCaller< MatrixTest > (
      "testAccessing",
      &MatrixTest::testAccessing
    )
  );
  
  return suite;
}
