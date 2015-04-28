#ifndef ELLIPSOID_METHOD
#define ELLIPSOID_METHOD

#include <algorithm>

#include "ConstraintList.h"
#include "Matrix.h"



template< typename T, std::size_t Dimension >
class EllipsoidMethod
{
  typedef T value_t;
  typedef Matrix< T > matrix_t;
  typedef Point< value_t, Dimension > point_t;
  typedef Constraint< value_t, Dimension > constraint_t;
  typedef ConstraintList< value_t, Dimension > constraint_list_t;



public:

  point_t optimize( const constraint_t& objective,
    const constraint_list_t& constraints,
    const value_t& R,
    const point_t& x0 )
  {
    const std::size_t n = Dimension;
    point_t xk = x0;
    matrix_t Bk = matrix_t::Type::Identity( n );
    value_t hk = R / ( n + 1 );
    
    while( this->calculate_subgradient( objective, constraints, xk ) != value_t( 0 ) ) {
    
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
