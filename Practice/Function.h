#ifndef FUNCTION_H
#define FUNCTION_H

#include "Point.h"



template< typename T, std::size_t N >
class Function
{
  typedef T value_t;
  typedef Point< value_t, N > point_t;



public:

  virtual ~Function()
  {
  
  }



  virtual value_t operator() ( const point_t& x );

};



#endif // FUNCTION_H
