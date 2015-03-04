#include "MatrixTest.h"

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include <Debug/PrintMatrix.h>



CPPUNIT_TEST_SUITE_REGISTRATION( MatrixTest );



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
  CPPUNIT_ASSERT( m0 != m1 );
  
  Matrix< int32_t > m2( m1 );
  CPPUNIT_ASSERT( m2 == m1 );
  
  Matrix< int32_t > m3( Matrix< int32_t >( 3, 4, 5 ) );
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



void MatrixTest::testAssignment()
{
  Matrix< float > m0( 3, 4 );
  Matrix< float > m1( 5, 6, 7.0 );
  m0 = m1;
  CPPUNIT_ASSERT( m0 == m1 );
  
  Matrix< float > m2( 2, 3 );
  m0 = std::move( m2 );
  CPPUNIT_ASSERT( m0 == m2 );
}



void MatrixTest::testAddition()
{
  Matrix< double > m0( 2, 3, 4.0 );
  Matrix< double > m1( 2, 3, 5.0 );
  Matrix< double > m2( 2, 3, 9.0 );

  Matrix< double > m3 = m0 + m1;
  CPPUNIT_ASSERT( m3 == m2 );

  Matrix< double > m4 = m2 - m1;
  CPPUNIT_ASSERT( m4 == m0 );
  
  m0 += m1;
  CPPUNIT_ASSERT( m0 == m2 );
  
  m1 -= m0;
  CPPUNIT_ASSERT( m1 == Matrix< double >( 2, 3, -4.0 ) );
}



void MatrixTest::testMultiplication()
{
  Matrix< int32_t > m0( 2, 3 );
  m0( 0, 0 ) = 2;  m0( 0, 1 ) = 3;  m0( 0, 2 ) = 4;
  m0( 1, 0 ) = 1;  m0( 1, 1 ) = 0;  m0( 1, 2 ) = 0;
  
  Matrix< int32_t > m1( 3, 2 );
  m1( 0, 0 ) = 0;  m1( 0, 1 ) = 1000;
  m1( 1, 0 ) = 1;  m1( 1, 1 ) = 100;
  m1( 2, 0 ) = 0;  m1( 2, 1 ) = 10;
  
  Matrix< int32_t > m2( 2, 2 );
  m2( 0, 0 ) = 3;  m2( 0, 1 ) = 2340;
  m2( 1, 0 ) = 0;  m2( 1, 1 ) = 1000;
  
  Matrix< int32_t > m3 = m0 * m1;
  CPPUNIT_ASSERT( m3 == m2 );
}
