#ifndef CONSTRAINT_LIST
#define CONSTRAINT_LIST

#include <vector>

#include "Constraint.h"



template< typename T, std::size_t Dimension >
class ConstraintList
{
  typedef T value_t;
  typedef Point< value_t, Dimension > point_t;
  typedef Function< value_t, Dimension > function_t;
  typedef Function< value_t, Dimension >* function_ptr_t;
  typedef Subgradient< point_t > subgradient_t;
  typedef Subgradient< point_t >* subgradient_ptr_t;
  typedef Constraint< T, Dimension > constraint_t;
  typedef std::vector< constraint_t > container_t;
  typedef typename container_t::iterator iterator_t;
  typedef typename container_t::const_iterator const_iterator_t;
  typedef typename container_t::size_type index_t;



public:

  void add( const function_ptr_t function_ptr, const subgradient_ptr_t subgradient_ptr )
  {
    constraint_t constraint( function_ptr, subgradient_ptr );
    
    this->container.push_back( constraint );
  }



  constraint_t& operator[] ( index_t index )
  {
    return this->container[ index ];
  }



  const constraint_t& operator[] ( index_t index ) const
  {
    return this->container[ index ];
  }



  index_t size() const
  {
    return this->container.size();
  }



  iterator_t begin()
  {
    return this->container.begin();
  }



  iterator_t end()
  {
    return this->container.end();
  }



  const_iterator_t begin() const
  {
    return this->container.begin();
  }



  const_iterator_t end() const
  {
    return this->container.end();
  }



private:

  container_t container;
};



#endif // CONSTRAINT_LIST
