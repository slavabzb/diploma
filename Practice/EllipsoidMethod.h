#ifndef ELLIPSOID_METHOD
#define ELLIPSOID_METHOD

#include <algorithm>

#include "ConstraintList.h"
#include "Matrix.h"



template< typename T, std::size_t Dimension >
class EllipsoidMethod
{
  static_assert( Dimension >= 2u, "Dimension of space is too small" );

  typedef T value_t;
  typedef Matrix< T > matrix_t;
  typedef Point< value_t, Dimension > point_t;
  typedef Constraint< value_t, Dimension > constraint_t;
  typedef ConstraintList< value_t, Dimension > constraint_list_t;



public:

  point_t optimize( const constraint_t& objective,
    const constraint_list_t& constraints,
    const value_t& ballRadius,
    const point_t& initialPoint )
  {
    const std::size_t n = Dimension;
    value_t hk = ballRadius / ( n + 1 );
    point_t xk = initialPoint;
    const matrix_t E = matrix_t::Type::Identity( n );
    matrix_t Bk( E );
    
    point_t g_xk = this->calculate_subgradient( objective, constraints, xk );
    while( g_xk != value_t( 0 ) ) {
      point_t ksi = Bk.transpose() * g_xk;
      ksi = ksi * ( 1.0 / ksi.norm() );
      xk = ( xk - ( Bk * hk ) * ksi );
      
      const value_t beta = std::sqrt( (n-1) / (n+1) );
      Bk = Bk * ( E - ( ksi * ( beta - 1 ) ) * ksi.transpose() );
      
      const value_t r = ( n / std::sqrt( std::pow( n, 2 ) - 1 ) );
      hk *= r;
      
      g_xk = this->calculate_subgradient( objective, constraints, xk );
    }  
    
    return xk;
  }



private:

  point_t calculate_subgradient( const constraint_t& objective,
    const constraint_list_t& constraints, const point_t& point )
  {
    auto max = std::max_element( constraints.begin(), constraints.end(),
      [ & ]( const constraint_t& lhs, const constraint_t& rhs ) -> bool {
        return ( lhs.function( point ) < rhs.function( point ) );
      } );
    
    point_t subgradient_at_point;
    if( ( *max ).function( point ) <= value_t( 0 ) ) {
      subgradient_at_point = objective.subgradient( point );
    }
    else {
      subgradient_at_point = ( *max ).subgradient( point );
    }
    
    return subgradient_at_point;
  }
};



#endif // ELLIPSOID_METHOD
