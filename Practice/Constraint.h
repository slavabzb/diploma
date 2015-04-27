#ifndef CONSTRAINT
#define CONSTRAINT

#include "Function.h"
#include "Subgradient.h"



template< typename T, std::size_t Dimension >
class Constraint
{
  typedef T value_t;
  typedef Point< value_t, Dimension > point_t;
  typedef Function< value_t, Dimension > function_t;
  typedef Function< value_t, Dimension >* function_ptr_t;
  typedef Subgradient< point_t > subgradient_t;
  typedef Subgradient< point_t >* subgradient_ptr_t;
  typedef std::pair< function_ptr_t, subgradient_ptr_t > container_t;



public:

  Constraint( const function_ptr_t function_ptr, const subgradient_ptr_t subgradient_ptr )
    : container( std::make_pair( function_ptr, subgradient_ptr ) )
  {
    
  }



  value_t function( const point_t& point ) const
  {
    return ( *this->container.first )( point );
  }



  point_t subgradient( const point_t& point ) const
  {
    return ( *this->container.second )( point );
  }



private:

  container_t container;
};


#endif // CONSTRAINT
