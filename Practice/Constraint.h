#ifndef CONSTRAINT
#define CONSTRAINT

#include <functional>

#include "Point.h"



template< typename T, std::size_t Dimension >
class Constraint
{
  typedef T value_t;
  typedef Point< value_t, Dimension > point_t;
  typedef std::function< value_t( const point_t& ) > function_t;
  typedef std::function< point_t( const point_t& ) > subgradient_t;
  typedef std::pair< function_t, subgradient_t > container_t;



public:

  Constraint( const function_t& function, const subgradient_t& subgradient )
    : container( std::make_pair( function, subgradient ) )
  {
    
  }



  value_t function( const point_t& point ) const
  {
    return ( this->container.first )( point );
  }



  point_t subgradient( const point_t& point ) const
  {
    return ( this->container.second )( point );
  }



private:

  container_t container;
};


#endif // CONSTRAINT
