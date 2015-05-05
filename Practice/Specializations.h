#ifndef SPECIALIZATIONS
#define SPECIALIZATIONS

#include <gmpxx.h>


namespace std
{

mpz_class pow( const mpz_class& base, uint64_t exp )
{
  mpz_class result;
  mpz_pow_ui( result.get_mpz_t(), base.get_mpz_t(), exp );
  
  return result;
}



mpz_class sqrt( const mpz_class& base, uint64_t exp )
{
  mpz_class result;
  mpz_pow_ui( result.get_mpz_t(), base.get_mpz_t(), exp );
  
  return result;
}

}



#endif // SPECIALIZATIONS
