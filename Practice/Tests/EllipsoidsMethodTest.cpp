#include "EllipsoidsMethodTest.h"

#include <gmpxx.h>

#include "ConstraintList.h"
#include "EllipsoidsMethod.h"

#include "HelperClasses/MatrixPrinter.h"
#include "HelperClasses/TimeMeasurer.h"


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

  /**
   * f0 = x1^2 + ( x2 - 2 )^2
   */
  auto objective_function = []( const point_t& x ) -> value_t {
    return ( std::pow( x[0], 2 ) + std::pow( x[1] - 2, 2 ) );
  };

  /**
   * f1 = x1^2 + x2^2 - 9
   */
  auto constraint_1 = []( const point_t& x ) -> value_t {
    return ( std::pow( x[0], 2 ) + std::pow( x[1], 2 ) - 9 );
  };
  
  /**
   * f2 = x1^2 + ( x2 - 4 )^2 - 9
   */
  auto constraint_2 = []( const point_t& x ) -> value_t {
    return ( std::pow( x[0], 2 ) + std::pow( x[1] - 4, 2 ) - 9 );
  };
  
  /**
   * g0 = ( 2 * x1, 2 * ( x2 - 2 ) )
   */
  auto objective_subgradient = []( const point_t& x ) -> point_t {
    return point_t{ 2 * x[0], 2 * ( x[1] - 2 ) };
  };
  
  /**
   * g1 = ( 2 * x1, 2 * x2 )
   */
  auto subgradient_1 = []( const point_t& x ) -> point_t {
    return point_t{ 2 * x[0], 2 * x[1] };
  };

  /**
   * g2 = ( 2 * x1, 2 * ( x2 - 4 ) )
   */
  auto subgradient_2 = []( const point_t& x ) -> point_t {
    return point_t{ 2 * x[0], 2 * ( x[1] - 4 ) };
  };
  
  Constraint< value_t, Dimension > objective( objective_function,
    objective_subgradient
  );
  
  ConstraintList< value_t, Dimension > constraints;
  constraints.add( constraint_1, subgradient_1 );
  constraints.add( constraint_2, subgradient_2 );
  
  const point_t initial_point{ 1.0, 2.0 };  
  const value_t ball_radius = 10.0;
  const value_t epsilon = 10e-10;
  const std::size_t iteration_limit = 1000;
  
  EllipsoidsMethod< value_t, Dimension > ellipsoids_method;
  point_t point = ellipsoids_method.optimize( objective,
    constraints,
    initial_point,
    ball_radius,
    epsilon,
    iteration_limit
  );
  
  std::cout << "Iterations: " << ellipsoids_method.get_iterations();
  
  MatrixPrinter matrix_printer( &std::cout );
  matrix_printer.set_precision( 20 );
  matrix_printer.print( point );
}



void EllipsoidsMethodTest::test_em_large_problem()
{
  typedef mpf_class value_t;
  const std::size_t Dimension = 50;
  typedef Point< value_t, Dimension > point_t;
  
  /**
   * f0 = x1^2 + x2^2 + ... + xn^2
   */
  auto objective_function = []( const point_t& x ) -> value_t {
    value_t result = 0;
    for( std::size_t i = 0; i < Dimension; ++i ) {
      result += std::pow( x[ i ], 2 );
    }
        
    return ( result );
  };
  
  /**
   * g0 = ( 2 * x1, 2 * x2, ... , 2 * xn )
   */
  auto objective_subgradient = []( const point_t& x ) -> point_t {
    point_t result;
    for( std::size_t i = 0; i < result.size(); ++i ) {
      result[ i ] = ( 2 * x[ i ] );
    }
    
    return ( result );
  };
  
  Constraint< value_t, Dimension > objective( objective_function,
    objective_subgradient
  );
  
  const value_t alpha = 1;
  
  /**
   * fi = x1^2 + x2^2 + ... + ( xi - alpha / 2 )^2 + ... + xn^2 - 4
   */
  auto function = [ &alpha ]( const point_t& x, std::size_t index ) -> value_t {    
    value_t result = 0;
    for( std::size_t i = 0; i < Dimension; ++i ) {
      if( i != index ) {
        result += std::pow( x[ i ], 2 );
      }
      else {
        result += std::pow( x[ i ] - alpha / 2, 2 );
      }
    }
    
    result -= 4;
    
    return ( result );
  };

  /**
   * gi = ( 2 * x1, 2 * x2, ... , 2 * ( xi - alpha / 2 ), ... , 2 * xn )
   */
  auto subgradient = [ &alpha ]( const point_t& x,
    std::size_t index ) -> point_t
  {
    point_t result;
    for( std::size_t i = 0; i < result.size(); ++i ) {
      if( i != index ) {
        result[ i ] = ( 2 * x[ i ] );
      }
      else {
        result[ i ] = ( 2 * ( x[ i ] - alpha / 2 ) );
      }
    }
    
    return ( result );
  };
  
  ConstraintList< value_t, Dimension > constraints;
  const std::size_t n_constraints = Dimension;
  for( std::size_t i_constraint = 0; i_constraint < n_constraints;
    ++i_constraint )
  {
    auto function_adaptor = std::bind( function, std::placeholders::_1,
      i_constraint );
    auto subgradient_adaptor = std::bind( subgradient, std::placeholders::_1,
      i_constraint );
    
    constraints.add( function_adaptor , subgradient_adaptor );
  }

  point_t initial_point;
  for( std::size_t i = 0; i < initial_point.size(); ++i ) {
    initial_point[ i ] = 0.4;
  }
    
  const value_t ball_radius = 10.0;
  const value_t epsilon = 10e-10;
  const std::size_t iteration_limit = 1000;
  
  EllipsoidsMethod< value_t, Dimension > ellipsoids_method;
  point_t point = ellipsoids_method.optimize( objective,
    constraints,
    initial_point,
    ball_radius,
    epsilon,
    iteration_limit
  );
  
  std::cout << "Iterations: " << ellipsoids_method.get_iterations();
  
  MatrixPrinter matrix_printer( &std::cout );
  matrix_printer.set_precision( 20 );
  matrix_printer.print( point );
}
