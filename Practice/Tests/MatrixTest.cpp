#include "MatrixTest.h"

#include <cmath>

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>



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
  
  m0 *= m1;
  CPPUNIT_ASSERT( m0 == m3 );
  
  Matrix< int32_t > m4( 2, 3 );
  m4( 0, 0 ) = 1;  m4( 0, 1 ) =  8;  m4( 0, 2 ) = -3;
  m4( 1, 0 ) = 4;  m4( 1, 1 ) = -2;  m4( 1, 2 ) =  5;
  
  Matrix< int32_t > m5( 2, 3 );
  m5( 0, 0 ) = 2;  m5( 0, 1 ) = 16;  m5( 0, 2 ) = -6;
  m5( 1, 0 ) = 8;  m5( 1, 1 ) = -4;  m5( 1, 2 ) = 10;
  
  const int32_t value = 2;
  CPPUNIT_ASSERT( value * m4 == m5 );
  
  const uint64_t N = 500;
  Matrix< uint64_t > A( N, N );
  Matrix< uint64_t > E( N, N, 1.0 );
  Matrix< uint64_t > R( A );
  
  for( uint64_t i = 1; i <= N; ++i ) {
    uint64_t sum = 0;
    for( uint64_t j = 1; j <= N; ++j ) {
      A( i-1, j-1 ) = i + j - 1;
      sum += i + j - 1;
    }
    for( uint64_t j = 1; j <= N; ++j ) {
      R( i-1, j-1 ) = sum;
    }
  }
    
  CPPUNIT_ASSERT( A * E == R );
}



void MatrixTest::testTransposition()
{
  Matrix< int32_t > m0( 2, 3 );
  m0( 0, 0 ) = 1;  m0( 0, 1 ) =  2;  m0( 0, 2 ) = 3;
  m0( 1, 0 ) = 0;  m0( 1, 1 ) = -6;  m0( 1, 2 ) = 7;
  
  Matrix< int32_t > m1( 3, 2 );
  m1( 0, 0 ) = 1;  m1( 0, 1 ) =  0;
  m1( 1, 0 ) = 2;  m1( 1, 1 ) = -6;
  m1( 2, 0 ) = 3;  m1( 2, 1 ) =  7;
  
  CPPUNIT_ASSERT( m0.transpose() == m1 );
  CPPUNIT_ASSERT( m1.transpose() == m0 );
}
