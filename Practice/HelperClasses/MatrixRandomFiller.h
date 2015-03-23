#ifndef MATRIX_RANDOM_FILLER
#define MATRIX_RANDOM_FILLER

#include <chrono>
#include <random>

#include "MatrixOperationPerformer.h"
#include "parallel_for.h"



class MatrixRandomFiller : public MatrixOperationPerformer
{
public:

  template< typename T >
  void fill( Matrix< T >& matrix )
  {
    uint64_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator( seed );
    std::uniform_real_distribution<> distribution( 0, 1 );
    
    auto fill = [ & ]( std::size_t iRowStart, std::size_t iRowEnd ) -> void
    {
      for( std::size_t iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( std::size_t jColumn = 0; jColumn < matrix.get_columns(); ++jColumn ) {
          matrix( iRow, jColumn ) = distribution( generator );
        }
      }
    };
    
    std::size_t first = 0;
    std::size_t last = matrix.get_rows();
    parallel_for( first, last, fill );  
  }
  
};



#endif // MATRIX_RANDOM_FILLER
