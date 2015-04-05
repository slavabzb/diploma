#ifndef MATRIX_RANDOM_FILLER
#define MATRIX_RANDOM_FILLER

#include <chrono>
#include <random>

#include "MatrixOperationPerformer.h"



class MatrixRandomFiller : public MatrixOperationPerformer
{
public:

  template< typename T >
  void fill( Matrix< T >& matrix )
  {
    uint64_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator( seed );
    std::uniform_real_distribution<> distribution( 0, 1 );
    
    for( std::size_t iRow = 0; iRow < matrix.get_rows(); ++iRow ) {
      for( std::size_t jColumn = 0; jColumn < matrix.get_columns(); ++jColumn ) {
        matrix( iRow, jColumn ) = distribution( generator );
      }
    }
  }
  
};



#endif // MATRIX_RANDOM_FILLER
