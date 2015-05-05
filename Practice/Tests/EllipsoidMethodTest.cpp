#include "EllipsoidMethodTest.h"

#include <gmpxx.h>

#include "ConstraintList.h"
#include "EllipsoidMethod.h"



CPPUNIT_TEST_SUITE_REGISTRATION( EllipsoidMethodTest );



void EllipsoidMethodTest::testPoint()
{
  Point< double, 5 > point5d{ 1.0, 2.0, 3.0 };
  Point< double, 5 > point5d_copy{ 1.0, 2.0, 3.0, 0.0, 0.0 };
  CPPUNIT_ASSERT( point5d == point5d_copy );
  CPPUNIT_ASSERT( point5d.size() == 5 );
  
  point5d[ 4 ] = 8;
  CPPUNIT_ASSERT( point5d[ 4 ] == 8 );
  CPPUNIT_ASSERT( point5d != point5d_copy );
  
  point5d = point5d_copy;
  CPPUNIT_ASSERT( point5d == point5d_copy );
  
  Point< int, 2 > lhs{ 1, 2 };
  Point< int, 2 > rhs{ 3, 4 };
  Point< int, 2 > result{ 4, 6 };
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



void EllipsoidMethodTest::testEllipsoidMethod()
{
  typedef mpf_class value_t;
  const std::size_t Dimension = 2;
  typedef Point< value_t, Dimension > point_t;
  
  // x1 + x2 <= 11
  auto constraint_1 = []( const point_t& x ) {
    return x[0] + x[1] - 11;
  };

  // g1 = ( 1, 1 )
  auto subgradient_1 = []( const point_t& x ) {
    return point_t{ 1.0, 1.0 };
  };

  // 4 * x1 - x2 <= 4
  auto constraint_2 = []( const point_t& x ) {
    return 4 * x[0] - x[1] - 4;
  };

  // g2 = ( 4, -1 )
  auto subgradient_2 = []( const point_t& x ) {
    return point_t{ 4.0, -1.0 };
  };

  // x1 >= 0
  auto constraint_3 = []( const point_t& x ) {
    return -x[0];
  };

  // g3 = ( -1, 0 )
  auto subgradient_3 = []( const point_t& x ) {
    return point_t{ -1.0, 0.0 };
  };

  // x2 >= 0
  auto constraint_4 = []( const point_t& x ) {
    return -x[1];
  };

  // g4 = ( 0, -1 )
  auto subgradient_4 = []( const point_t& x ) {
    return point_t{ 0.0, -1.0 };
  };

  // f( x1, x2 ) = ( x1 - 5 )^2 + ( x2 - 10 )^2
  auto objectiveFunction = []( const point_t& x ) {
    return ( std::pow( x[0] - 5, 2 ) + std::pow( x[1] - 10, 2 ) );
  };

  // grad f( x1, x2 ) = ( 2 * x1, 2 * x2 )
  auto objectiveSubgradient = []( const point_t& x ) {
    return point_t{ 2 * x[0], 2 * x[1] };
  };
  
  Constraint< value_t, Dimension > objective( objectiveFunction, objectiveSubgradient );
  
  ConstraintList< value_t, Dimension > constraints;
  constraints.add( constraint_1, subgradient_1 );
  constraints.add( constraint_2, subgradient_2 );
  constraints.add( constraint_3, subgradient_3 );
  constraints.add( constraint_4, subgradient_4 );
  
  EllipsoidMethod< value_t, Dimension > ellipsoidMethod;
  const value_t ballRadius = 1.0;
  const point_t initialPoint{ 0.0, 0.0 };
  point_t point = ellipsoidMethod.optimize( objective,
    constraints, ballRadius, initialPoint );
  
  point.print();
}
