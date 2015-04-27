#ifndef EXAMPLE_1
#define EXAMPLE_1

#include <gmpxx.h>

#include "Function.h"
#include "Subgradient.h"



class Function1 : public Function< mpz_class, 2 >
{
public:

  mpz_class operator() ( const ::Point< mpz_class, 2 >& point ) const override
  { // f(x) = x1^2+|x2|^3
    mpz_class lhs;
    mpz_ui_pow_ui( lhs.get_mpz_t(), point[ 0 ].get_ui(), 2 );
       
    mpz_class rhs_abs;
    mpz_abs( rhs_abs.get_mpz_t(), point[ 1 ].get_mpz_t() );
    
    mpz_class rhs;
    mpz_ui_pow_ui( rhs.get_mpz_t(), rhs_abs.get_ui(), 3 );
    
    mpz_class result = ( lhs + rhs );
    
    return result;
  }
};



#endif // EXAMPLE_1
