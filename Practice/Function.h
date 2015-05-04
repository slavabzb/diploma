#ifndef FUNCTION_H
#define FUNCTION_H

#include "Point.h"



template< typename T, std::size_t Dimension >
class Function
{
protected:

  typedef T value_t;
  typedef Point< value_t, Dimension > point_t;



public:

  virtual ~Function()
  {
  
  }



  virtual value_t operator() ( const point_t& point ) const = 0;
};



#endif // FUNCTION_H
