#ifndef MATRIX_TRANSPOSER
#define MATRIX_TRANSPOSER

#include "MatrixOperationPerformer.h"



class MatrixTransposer : public MatrixOperationPerformer
{
public:

  template< typename T >
  void transpose( Matrix< T >& result, const Matrix< T >& lhs )
  {
    assert( result.get_rows() == lhs.get_columns() );
    assert( result.get_columns() == lhs.get_rows() );
  
    for( std::size_t iRow = 0; iRow < lhs.get_rows(); ++iRow ) {
      for( std::size_t jColumn = 0; jColumn < lhs.get_columns(); ++jColumn ) {
        result( jColumn, iRow ) = lhs( iRow, jColumn );
      }
    }
  }

};



#endif // MATRIX_TRANSPOSER
