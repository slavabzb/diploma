#ifndef MATRIX_SUMMARIZER
#define MATRIX_SUMMARIZER

#include "MatrixOperationPerformer.h"



class MatrixSummarizer : public MatrixOperationPerformer
{
public:

  template< typename T >
  void sum( Matrix< T >& result, const Matrix< T >& lhs, const Matrix< T >& rhs )
  {
    assert( lhs.get_rows() == rhs.get_rows() );
    assert( lhs.get_columns() == rhs.get_columns() );
    assert( result.get_rows() == lhs.get_rows() );
    assert( result.get_columns() == lhs.get_columns() );
    
    for( std::size_t iRow = 0; iRow < lhs.get_rows(); ++iRow ) {
      for( std::size_t jColumn = 0; jColumn < rhs.get_columns(); ++jColumn ) {
        result( iRow, jColumn ) = lhs( iRow, jColumn ) + rhs( iRow, jColumn );
      }
    }
  }

};



#endif // MATRIX_SUMMARIZER
