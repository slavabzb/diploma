#ifndef ELLIPSOID_METHOD
#define ELLIPSOID_METHOD

#include "ConstraintList.h"



template< typename T, std::size_t Dimension >
class EllipsoidMethod
{
  typedef T value_t;
  typedef Point< value_t, Dimension > point_t;
  typedef Constraint< value_t, Dimension > constraint_t;
  typedef ConstraintList< value_t, Dimension > constraint_list_t;



public:

  point_t optimize( const constraint_t& objective, const constraint_list_t& constraints )
  {
    point_t optimalPoint;
    
    return optimalPoint;
  }
};



#endif // ELLIPSOID_METHOD
