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



mpf_class sqrt( const mpf_class& value )
{
  mpf_class result;
  mpf_sqrt( result.get_mpf_t(), value.get_mpf_t() );
  
  return result;
}

} // namespace std



#endif // SPECIALIZATIONS
