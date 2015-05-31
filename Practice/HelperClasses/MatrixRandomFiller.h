#ifndef MATRIX_RANDOM_FILLER
#define MATRIX_RANDOM_FILLER

#include <chrono>
#include <random>

#include "ParallelHandler.h"



class MatrixRandomFiller
{
public:

  template< typename T >
  void fill( Matrix< T >& matrix )
  {
    uint64_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator( seed );
    std::uniform_real_distribution<> distribution( 0, 1 );

    auto fill = [ & ]( std::size_t first, std::size_t last ) -> void
    {
      for( std::size_t row = first; row < last; ++row ) {
        for( std::size_t column = 0; column < matrix.get_columns(); ++column ) {
          matrix( row, column ) = distribution( generator );
        }
      }
    };

    const std::size_t first = 0;
    const std::size_t last = matrix.get_rows();

    ParallelHandler parallel_handler;
    parallel_handler.parallel_for( first, last, fill );
  }
  
};



#endif // MATRIX_RANDOM_FILLER
