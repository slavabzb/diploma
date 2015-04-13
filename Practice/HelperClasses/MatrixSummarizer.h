#ifndef MATRIX_SUMMARIZER
#define MATRIX_SUMMARIZER

#include "MatrixOperationPerformer.h"



class MatrixSummarizer : public MatrixOperationPerformer
{
public:

  template< typename T >
  void summarize( Matrix< T >& result, const Matrix< T >& lhs, const Matrix< T >& rhs )
  {
#ifdef TIME_TEST

    assert( lhs.get_rows_nonblock() == rhs.get_rows_nonblock() );
    assert( lhs.get_columns_nonblock() == rhs.get_columns_nonblock() );
    assert( result.get_rows_nonblock() == lhs.get_rows_nonblock() );
    assert( result.get_columns_nonblock() == lhs.get_columns_nonblock() );
    
    for( std::size_t iRow = 0; iRow < lhs.get_rows_nonblock(); ++iRow ) {
      for( std::size_t jColumn = 0; jColumn < rhs.get_columns_nonblock(); ++jColumn ) {
        result.get_nonblock( iRow, jColumn ) = ( 
          lhs.get_nonblock( iRow, jColumn ) + rhs.get_nonblock( iRow, jColumn )
        );
      }
    }

#else

    assert( lhs.get_rows() == rhs.get_rows() );
    assert( lhs.get_columns() == rhs.get_columns() );
    assert( result.get_rows() == lhs.get_rows() );
    assert( result.get_columns() == lhs.get_columns() );
    
    for( std::size_t iRow = 0; iRow < lhs.get_rows(); ++iRow ) {
      for( std::size_t jColumn = 0; jColumn < rhs.get_columns(); ++jColumn ) {
        result( iRow, jColumn ) = lhs( iRow, jColumn ) + rhs( iRow, jColumn );
      }
    }

#endif // TIME_TEST

  }

};



#endif // MATRIX_SUMMARIZER
