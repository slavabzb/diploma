#ifndef EXAMPLE_2
#define EXAMPLE_2

#include <gmpxx.h>

#include "Function.h"
#include "Subgradient.h"



class Function2 : public Function< mpz_class, 6 >
{
public:

  mpz_class operator() ( const Point< mpz_class, 6 >& point ) const override
  { // f2(x) = x1^2+10x2^2+30x3^2+50x4^2+90x5^2+100x6^2
    mpz_class result;
    mpz_class value;
    
    mpz_pow_ui( value.get_mpz_t(), point[ 0 ].get_mpz_t(), 2 );
    result += value;
    
    mpz_pow_ui( value.get_mpz_t(), point[ 1 ].get_mpz_t(), 2 );
    result += ( 10 * value );
    
    mpz_pow_ui( value.get_mpz_t(), point[ 2 ].get_mpz_t(), 2 );
    result += ( 30 * value );
    
    mpz_pow_ui( value.get_mpz_t(), point[ 3 ].get_mpz_t(), 2 );
    result += ( 50 * value );
    
    mpz_pow_ui( value.get_mpz_t(), point[ 4 ].get_mpz_t(), 2 );
    result += ( 90 * value );
    
    mpz_pow_ui( value.get_mpz_t(), point[ 5 ].get_mpz_t(), 2 );
    result += ( 100 * value );
    
    return result;
  }
};



class Function2Subgradient : public Subgradient< Point< mpz_class, 6 > >
{
public:

  Point< mpz_class, 6 > operator() ( const Point< mpz_class, 6 >& point ) const override
  { // grad f2(x) = ( 2x1, 20x2, 60x3, 100x4, 180x5, 200x6 )
    Point< mpz_class, 6 > result(
      2   * point[ 0 ],
      20  * point[ 1 ],
      60  * point[ 2 ],
      100 * point[ 3 ],
      180 * point[ 4 ],
      200 * point[ 5 ]
    );
    
    return result;
  }
};



#endif // EXAMPLE_2
