#ifndef EXAMPLE
#define EXAMPLE

#include <cmath>

#include "Function.h"



class ExampleFunction : public Function< double, 2 >
{
public:

  value_t operator() ( const point_t& x ) const override
  { // f( x1, x2 ) = ( x1 - 5 )^2 + ( x2 - 10 )^2
    return ( std::pow( x[0] - 5, 2 ) + std::pow( x[1] - 10, 2 ) );
  }
};



class ExampleFunctionSubgradient : public Subgradient< Point< double, 2 > >
{
public:

  point_t operator() ( const point_t& x ) const override
  { // grad f( x1, x2 ) = ( 2 * x1, 2 * x2 )
    return point_t( 2 * x[0], 2 * x[1] );
  }
};



class ExampleConstraintList : public ConstraintList< double, 2 >
{
  typedef Point< double, 2 > point_t;



public:

  ExampleConstraintList()
  {
//    // x1 + x2 <= 11
//    auto constraint_1 = []( const point_t& x ) {
//      return x[0] + x[1] - 11;
//    };
//    
//    // g1 = ( 1, 1 )
//    auto subgradient_1 = []( const point_t& x ) {
//      return point_t( 1.0, 1.0 );
//    };
//    
//    // 4 * x1 - x2 <= 4
//    auto constraint_2 = []( const point_t& x ) {
//      return 4 * x[0] - x[1] - 4;
//    };
//    
//    // g2 = ( 4, -1 )
//    auto subgradient_2 = []( const point_t& x ) {
//      return point_t( 4.0, -1.0 );
//    };
//    
//    // x1 >= 0
//    auto constraint_3 = []( const point_t& x ) {
//      return -x[0];
//    };
//    
//    // g3 = ( -1, 0 )
//    auto subgradient_3 = []( const point_t& x ) {
//      return point_t( -1.0, 0.0 );
//    };
//    
//    // x2 >= 0
//    auto constraint_4 = []( const point_t& x ) {
//      return -x[1];
//    };
//    
//    // g4 = ( 0, -1 )
//    auto subgradient_4 = []( const point_t& x ) {
//      return point_t( 0.0, -1.0 );
//    };
//    
//    this->add( &constraint_1, &subgradient_1 );
//    this->add( &constraint_2, &subgradient_2 );
//    this->add( &constraint_3, &subgradient_3 );
//    this->add( &constraint_4, &subgradient_4 );
  }
};

#endif // EXAMPLE
