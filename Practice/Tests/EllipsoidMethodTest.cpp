#include "EllipsoidMethodTest.h"

#include "ConstraintList.h"
#include "EllipsoidMethod.h"
#include "Example1.h"
#include "Example2.h"



CPPUNIT_TEST_SUITE_REGISTRATION( EllipsoidMethodTest );



void EllipsoidMethodTest::testPoint()
{
  Point< double, 5 > point5d( 1.0, 2.0, 3.0 );
  Point< double, 5 > point5d_copy( 1.0, 2.0, 3.0, 0.0, 0.0 );
  CPPUNIT_ASSERT( point5d == point5d_copy );
  CPPUNIT_ASSERT( point5d.size() == 5 );
  
  point5d[ 4 ] = 8;
  CPPUNIT_ASSERT( point5d[ 4 ] == 8 );
  CPPUNIT_ASSERT( point5d != point5d_copy );
  
  point5d = point5d_copy;
  CPPUNIT_ASSERT( point5d == point5d_copy );
  
  Point< int, 2 > lhs( 1, 2 );
  Point< int, 2 > rhs( 3, 4 );
  Point< int, 2 > result( 4, 6 );
  CPPUNIT_ASSERT( result == (lhs + rhs) );
  
  result[ 0 ] = 2;
  result[ 1 ] = 2;
  CPPUNIT_ASSERT( result == 2 );
  CPPUNIT_ASSERT( result == (rhs - lhs) );
  
  rhs -= lhs;
  CPPUNIT_ASSERT( result == rhs );
  
  result += lhs;
  CPPUNIT_ASSERT( result[ 0 ] == 3 );
  CPPUNIT_ASSERT( result[ 1 ] == 4 );
  CPPUNIT_ASSERT( result != 2 );
}



void EllipsoidMethodTest::testEnvironment()
{  
  ConstraintList< mpz_class, 6 > constraintList;
  CPPUNIT_ASSERT( constraintList.size() == 0 );
  
  Function2 function2;
  Function2Subgradient function2Subgradient;
  constraintList.add( &function2, &function2Subgradient );
  CPPUNIT_ASSERT( constraintList.size() == 1 );
  
  Point< mpz_class, 6 > point2( 6, 5, 4, 3, 2, 1 );
  Point< mpz_class, 6 > value2( 2*6, 20*5, 60*4, 100*3, 180*2, 200*1 );
  mpz_class result2 = 1676;
  
  CPPUNIT_ASSERT( constraintList[ 0 ].function( point2 ) == result2 );
  CPPUNIT_ASSERT( constraintList[ 0 ].subgradient( point2 ) == value2 );
}



void EllipsoidMethodTest::testEllipsoidMethod()
{
  Function2 function2;
  Function2Subgradient function2Subgradient;
  Constraint< mpz_class, 6 > objective( &function2, &function2Subgradient );
  ConstraintList< mpz_class, 6 > constraints;
  
  EllipsoidMethod< mpz_class, 6 > ellipsoidMethod;
  ellipsoidMethod.optimize( objective, constraints );
}
