#include "EllipsoidsMethodTest.h"

#include <gmpxx.h>

#include "ConstraintList.h"
#include "EllipsoidsMethod.h"



CPPUNIT_TEST_SUITE_REGISTRATION( EllipsoidsMethodTest );



void EllipsoidsMethodTest::test_point()
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



void EllipsoidsMethodTest::test_ellipsoids_method()
{
  typedef mpf_class value_t;
  const std::size_t Dimension = 2;
  typedef Point< value_t, Dimension > point_t;
  
  // f1 = x1^2 + x2^2 - 9
  auto constraint_1 = []( const point_t& x ) -> value_t {
    return ( std::pow( x[0], 2 ) + std::pow( x[1], 2 ) - 9 );
  };

  // g1 = ( 2 * x1, 2 * x2 )
  auto subgradient_1 = []( const point_t& x ) -> point_t {
    return point_t{ 2 * x[0], 2 * x[1] };
  };

  // f2 = x1^2 + ( x2 - 4 )^2 - 9
  auto constraint_2 = []( const point_t& x ) -> value_t {
    return ( std::pow( x[0], 2 ) + std::pow( x[1] - 4, 2 ) - 9 );
  };

  // g2 = ( 2 * x1, 2 * ( x2 - 4 ) )
  auto subgradient_2 = []( const point_t& x ) -> point_t {
    return point_t{ 2 * x[0], 2 * ( x[1] - 4 ) };
  };

  // f0 = x1^2 + ( x2 - 2 )^2
  auto objective_function = []( const point_t& x ) -> value_t {
    return ( std::pow( x[0], 2 ) + std::pow( x[1] - 2, 2 ) );
  };

  // g0 = ( 2 * x1, 2 * ( x2 - 2 ) )
  auto objective_subgradient = []( const point_t& x ) -> point_t {
    return point_t{ 2 * x[0], 2 * ( x[1] - 2 ) };
  };
  
  Constraint< value_t, Dimension > objective( objective_function,
    objective_subgradient
  );
  
  ConstraintList< value_t, Dimension > constraints;
  constraints.add( constraint_1, subgradient_1 );
  constraints.add( constraint_2, subgradient_2 );
    
  EllipsoidsMethod< value_t, Dimension > ellipsoids_method;
  const value_t ball_radius = 10.0;
  const point_t initial_point{ 1.0, 2.0 };
  const std::size_t iteration_limit = 1000;
  const value_t epsilon = 1e-9;
  point_t point = ellipsoids_method.optimize( objective,
    constraints,
    initial_point,
    ball_radius,
    epsilon,
    iteration_limit
  );
}
