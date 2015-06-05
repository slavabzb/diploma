#ifndef MATRIX_MULTIPLIER
#define MATRIX_MULTIPLIER



class MatrixMultiplier
{
public:

  template< typename T >
  void multiply( Matrix< T >& result, const Matrix< T >& lhs,
    const Matrix< T >& rhs )
  {
    assert( lhs.get_columns() == rhs.get_rows() );
    assert( result.get_rows() == lhs.get_rows() );
    assert( result.get_columns() == rhs.get_columns() );
    
    for( std::size_t row = 0; row < lhs.get_rows(); ++row ) {
      for( std::size_t column = 0; column < rhs.get_columns(); ++column ) {
        T sum = 0.0;
        for( std::size_t index = 0; index < lhs.get_columns(); ++index ) {
          sum += ( lhs( row, index ) * rhs( index, column ) );
        }
        result( row, column ) = sum;
      }
    }
  }



  template< typename T >
  void multiply( const T& value , Matrix< T >& rhs )
  {
    for( std::size_t row = 0; row < rhs.get_rows(); ++row ) {
      for( std::size_t column = 0; column < rhs.get_columns(); ++column ) {
        rhs( row, column ) *= value;
      }
    }
  }

};



#endif // MATRIX_MULTIPLIER
