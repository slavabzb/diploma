#ifndef CONSTRAINT_LIST
#define CONSTRAINT_LIST

#include <vector>

#include "Constraint.h"



/**
 * Represents a list of constraint functions.
 */
template< typename T, std::size_t Dimension >
class ConstraintList
{
  typedef T value_t;
  typedef Point< value_t, Dimension > point_t;
  typedef std::function< value_t( const point_t& ) > function_t;
  typedef std::function< point_t( const point_t& ) > subgradient_t;
  typedef Constraint< value_t, Dimension > constraint_t;
  typedef std::vector< constraint_t > container_t;
  typedef typename container_t::iterator iterator_t;
  typedef typename container_t::const_iterator const_iterator_t;
  typedef typename container_t::size_type index_t;



public:

  /**
   * Add a constraint to the list.
   * @param function a constraint function.
   * @param subgradient a subgradient of constraint function.
   */
  void add( const function_t& function, const subgradient_t& subgradient )
  {
    constraint_t constraint( function, subgradient );
    
    this->container.push_back( constraint );
  }



  /**
   * An accessor.
   * Retrieve a reference of the constraint by index.
   */
  constraint_t& operator[] ( index_t index )
  {
    return this->container[ index ];
  }



  /**
   * An accessor.
   * Retrieve a const reference of the constraint by index.
   */
  const constraint_t& operator[] ( index_t index ) const
  {
    return this->container[ index ];
  }



  /**
   * Retrieve a number of constraints in list.
   */
  index_t size() const
  {
    return this->container.size();
  }



  /**
   * Retrieve an iterator pointed to the first constraint of the list.
   */
  iterator_t begin()
  {
    return this->container.begin();
  }



  /**
   * Retrieve a const iterator pointed to the first constraint of the list.
   */
  const_iterator_t begin() const
  {
    return this->container.begin();
  }



  /**
   * Retrieve an iterator pointed to the next to the last constraint of the list.
   */
  iterator_t end()
  {
    return this->container.end();
  }



  /**
   * Retrieve a const iterator pointed to the next to the last constraint of
   * the list.
   */
  const_iterator_t end() const
  {
    return this->container.end();
  }



private:

  container_t container;
};



#endif // CONSTRAINT_LIST
