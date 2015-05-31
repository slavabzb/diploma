#ifndef MATRIX_SUMMARIZER
#define MATRIX_SUMMARIZER



class MatrixSummarizer
{
public:

  template< typename T >
  void summarize( Matrix< T >& result, const Matrix< T >& lhs, const Matrix< T >& rhs )
  {
    assert( lhs.get_rows() == rhs.get_rows() );
    assert( lhs.get_columns() == rhs.get_columns() );
    assert( result.get_rows() == lhs.get_rows() );
    assert( result.get_columns() == lhs.get_columns() );
    
    for( std::size_t row = 0; row < lhs.get_rows(); ++row ) {
      for( std::size_t column = 0; column < rhs.get_columns(); ++column ) {
        result( row, column ) = ( lhs( row, column ) + rhs( row, column ) );
      }
    }
  }

};



#endif // MATRIX_SUMMARIZER
