#ifndef ELLIPSOIDS_METHOD
#define ELLIPSOIDS_METHOD

#include <algorithm>

#include "ConstraintList.h"
#include "Matrix.h"



/**
 *  An implementation of Shor's ellipsoids method.
 */
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

  /**
   *  An implementation of ellipsoids method algorithm.
   *  @param objective a function to be optimized
   *  @param constraints a list of constraints of convex programming problem
   *  @param initial_point a point from where the optimization process starts
   *  @param ball_radius a radius of a ball which locates the optimal point
   *  @warning The precondition must be fulfilled || optimal_point - initial_point || <= ball_radius
   *  @param epsilon a stopping criterion for accuracy
   *  @param iteration_limit a stopping criterion for number of iterations
   *  @return The optimal point if success or initial point if failure
   */
  point_t optimize( const constraint_t& objective,
    const constraint_list_t& constraints,
    const point_t& initial_point,
    const value_t& ball_radius,
    const value_t& epsilon,
    std::size_t iteration_limit )
  {        
    value_t reduction = ball_radius / ( Dimension + 1.0 );
    point_t optimal_point = initial_point;
    
    const matrix_t identity = matrix_t::Type::Identity( Dimension );
    matrix_t inverse_transform_space( identity );
    
    point_t subgradient = this->calculate_subgradient( objective,
      constraints,
      optimal_point
    );
    
    std::size_t iteration = 0u;
    bool stopping_criterion = false;
    while( !stopping_criterion ) {
      point_t direction = inverse_transform_space.transpose() * subgradient;
      direction *= ( 1.0 / direction.norm() );
      
      optimal_point -= ( inverse_transform_space * reduction ) * direction;
      
      const value_t beta = std::sqrt( ( Dimension - 1.0 ) / ( Dimension + 1.0 ) );
      inverse_transform_space = inverse_transform_space * (
        identity + ( direction * direction.transpose() ) * ( beta - 1.0 )
      );    
      
      const value_t reduction_step = (
        Dimension / std::sqrt( std::pow( Dimension, 2 ) - 1.0 )
      );
      
      reduction *= reduction_step;
      
      subgradient = this->calculate_subgradient( objective,
        constraints,
        optimal_point
      );
      
      ++iteration;
      
      stopping_criterion = (
        ( subgradient.norm() < epsilon ) || ( iteration >= iteration_limit )
      );

    }
    
    std::cout << "\n" << iteration << "\n";
    
    subgradient.print( "g(xk)" );
    
    bool precondition = (
      static_cast<point_t>( optimal_point - initial_point ).norm() <= ball_radius
    );
    
    return precondition ? optimal_point : initial_point;
  }



private:

  point_t calculate_subgradient( const constraint_t& objective,
    const constraint_list_t& constraints,
    const point_t& point ) const
  {   
    auto max = std::max_element( constraints.begin(), constraints.end(),
      [ & ]( const constraint_t& lhs, const constraint_t& rhs ) -> bool {
        return ( lhs.function( point ) < rhs.function( point ) );
      } );
        
    point_t subgradient;
    if( ( *max ).function( point ) <= value_t( 0 ) ) {
      subgradient = objective.subgradient( point );
    }
    else {
      subgradient = ( *max ).subgradient( point );
    }
    
    return subgradient;
  }

};



#endif // ELLIPSOIDS_METHOD
