#ifndef SPECIALIZATIONS
#define SPECIALIZATIONS

#include <gmpxx.h>


namespace std {

mpf_class pow( const mpf_class& base, uint64_t exp )
{
  mpf_class result;
  mpf_pow_ui( result.get_mpf_t(), base.get_mpf_t(), exp );
  
  return result;
}



//mpz_class pow( const mpz_class& base, uint64_t exp )
//{
//  mpz_class result;
//  mpz_pow_ui( result.get_mpz_t(), base.get_mpz_t(), exp );
//  
//  return result;
//}



mpf_class sqrt( const mpf_class& value )
{
  mpf_class result;
  mpf_sqrt( result.get_mpf_t(), value.get_mpf_t() );
  
  return result;
}



//mpz_class sqrt( const mpz_class& value )
//{
//  mpz_class result;
//  mpz_sqrt( result.get_mpz_t(), value.get_mpz_t() );
//  
//  return result;
//}

} // namespace std



#endif // SPECIALIZATIONS
