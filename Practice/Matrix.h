#ifndef MATRIX
#define MATRIX

#include <assert.h>
#include <valarray>

#include "ParallelHandler.h"


/**
 *  Represents matrices.
 */
template< typename T >
class Matrix
{
private:

  typedef T value_t;
  typedef Matrix< value_t > my_t;
  typedef std::size_t index_t;



public:

  /**
   * A constructor.
   * Construct a rows-by-columns Matrix filled with the given value.
   */
  Matrix( index_t rows, index_t columns, const value_t& value = value_t( 0 ) )
    : values( value, rows * columns )
    , rows( rows )
    , columns( columns )
    , is_transposed( false )
  {
    assert( rows > 0 );
    assert( columns > 0 );
  }



  /**
   * A copy constructor.
   * Construct a copy of other Matrix object.
   */
  Matrix( const my_t& rhs )
    : values( rhs.values )
    , rows( rhs.rows )
    , columns( rhs.columns )
    , is_transposed( rhs.is_transposed )
  {

  }



  /**
   * A move constructor.
   * Construct a copy using resources of temporary Matrix object.
   */
  Matrix( my_t&& rhs )
    : values( std::move( rhs.values ) )
    , rows( rhs.rows )
    , columns( rhs.columns )
    , is_transposed( rhs.is_transposed )
  {

  }



  /**
   * An accessor.
   * Retrieve the reference.
   */
  value_t& operator() ( const index_t& row, const index_t& column )
  {    
    assert( row < this->get_rows() );
    assert( column < this->get_columns() );

    return this->get( row, column );
  }



  /**
   * A const accessor.
   * Retrieve the const reference.
   */
  const value_t& operator() ( const index_t& row, const index_t& column ) const
  {    
    assert( row < this->get_rows() );
    assert( column < this->get_columns() );

    return this->get( row, column );
  }



  /**
   * A copy-based assignment operator.
   * Make the matrix equal to other Matrix object.
   */
  my_t& operator= ( const my_t& rhs )
  {
    if( this == &rhs ) {
      return *this;
    }

    this->values = rhs.values;
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->is_transposed = rhs.is_transposed;

    return *this;
  }



  /**
   * A move-based assignment operator.
   * Make the matrix the owner of the resources of the temporary Matrix object.
   */
  my_t& operator= ( my_t&& rhs )
  {
    if (this == &rhs) {
      return *this;
    }

    this->values = std::move( rhs.values );
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->is_transposed = rhs.is_transposed;

    return *this;
  }



  /**
   * An addition operator.
   * Retrieve the Matrix each element of which is the sum of the corresponding
   * values of this and rhs Matrix objects.
   */
  my_t operator+ ( const my_t& rhs ) const
  {
    assert( this->get_rows() == rhs.get_rows() );
    assert( this->get_columns() == rhs.get_columns() );
    
    my_t result( this->get_rows(), this->get_columns() );
    
    auto summarize = [ this, &rhs, &result ]( const index_t& row_start,
      const index_t& row_end ) -> void
    {
      for( index_t row = row_start; row < row_end; ++row ) {
        for( index_t column = 0; column < this->get_columns(); ++column ) {
          result.get( row, column ) = (
            this->get( row, column ) + rhs.get( row, column ) 
          );
        }
      }
    };

    const index_t first = 0;
    const index_t last = this->get_rows();
    my_t::get_parallel_handler()->parallel_for( first, last, summarize );

    return result;
  }



  /**
   * A subtraction operator.
   * Retrieve the Matrix each element of which is the difference of the corresponding
   * values of this and rhs Matrix objects.
   */
  my_t operator- ( const my_t& rhs ) const
  {
    assert( this->get_rows() == rhs.get_rows() );
    assert( this->get_columns() == rhs.get_columns() );
    
    my_t result( this->get_rows(), this->get_columns() );
    
    auto subtract = [ this, &rhs, &result ]( const index_t& row_start,
      const index_t& row_end ) -> void
    {
      for( index_t row = row_start; row < row_end; ++row ) {
        for( index_t column = 0; column < this->get_columns(); ++column ) {
          result.get( row, column ) = (
            this->get( row, column ) - rhs.get( row, column )
          );
        }
      }
    };

    const index_t first = 0;
    const index_t last = this->get_rows();
    my_t::get_parallel_handler()->parallel_for( first, last, subtract );

    return result;
  }



  /**
   * A multiplication operator.
   * Retrieve the Matrix which is equal to result of matrix multiplication
   * of this and rhs Matrix objects.
   */
  my_t operator* ( const my_t& rhs ) const
  {
    assert( this->get_columns() == rhs.get_rows() );
    
    my_t result( this->get_rows(), rhs.get_columns() );
    
    auto multiply = [ this, &rhs, &result ]( const index_t& row_start,
      const index_t& row_end ) -> void
    {
      for( index_t row = row_start; row < row_end; ++row ) {
        for( index_t column = 0; column < rhs.get_columns(); ++column ) {
          for( index_t sIndex = 0; sIndex < this->get_columns(); ++sIndex ) {
            result.get( row, column ) += (
              this->get( row, sIndex ) * rhs.get( sIndex, column )
            );
          }
        }
      }
    };

    const index_t first = 0;
    const index_t last = this->get_rows();
    my_t::get_parallel_handler()->parallel_for( first, last, multiply );

    return result;
  }



  /**
   * A multiplication operator.
   * Multiply each element of the Matrix by value.
   */
  my_t operator* ( const T& value ) const
  {
    my_t result( *this );

    auto multiply = [ &result, &value ]( const index_t& row_start,
      const index_t& row_end ) -> void
    {
      for( index_t row = row_start; row < row_end; ++row ) {
        for( index_t column = 0; column < result.get_columns(); ++column ) {
          result.get( row, column ) *= value;
        }
      }
    };

    const index_t first = 0;
    const index_t last = result.get_rows();
    my_t::get_parallel_handler()->parallel_for( first, last, multiply );

    return result;
  }



  /**
   * A comparison operator.
   * Check if each element of the matrix is equal to the corresponding
   * element of the other Matrix object.
   */
  bool operator== ( const my_t& rhs ) const
  {
    if ( &rhs == this ) {
      return true;
    }

    bool rows_mismatch = ( this->get_rows() != rhs.get_rows() );
    bool columns_mismatch = ( this->get_columns() != rhs.get_columns() );
    
    if ( rows_mismatch || columns_mismatch ) {
      return false;
    }
    
    std::valarray< bool > comparison_result = ( this->values == rhs.values );
    bool is_equal = ( comparison_result.min() == true );
    
    return is_equal;
  }



  /**
   * A comparison operator.
   * Check if the matrix is not equal to the other Matrix object.
   */
  bool operator!= ( const my_t& rhs ) const
  {
    return !( *this == rhs );
  }



  /**
   * A transposition.
   * Swap rows and columns.
   */
  my_t transpose() const
  {
    my_t copy( *this );
    copy.is_transposed = !this->is_transposed;
    
    return copy;
  }



  /**
   * A number of rows.
   * Retrieve the number of rows of the matrix.
   */
  std::size_t get_rows() const
  {
    return ( this->is_transposed ? this->columns : this->rows );
  }



  /**
   * A number of columns.
   * Retrieve the number of columns of the matrix.
   */
  std::size_t get_columns() const
  {
    return ( this->is_transposed ? this->rows : this->columns );
  }



  /**
   * Retrieve an instance of parallel execution controller.
   */
  static ParallelHandler* get_parallel_handler()
  {
    static ParallelHandler parallel_handler;

    return &parallel_handler;
  }



  /**
   * Represents types of matrices.
   */
  class Type
  {
  public:
  
    /**
     * An identity matrix.
     * Retrieve an identity matrix.
     */
    static Matrix< T > identity( index_t size )
    {
      Matrix< T > identity_matrix( size, size );
      
      for( index_t index = 0; index < size; ++index ) {
        identity_matrix( index, index ) = value_t( 1 );
      }
      
      return identity_matrix;
    }
  };



private:

  /**
   * A private accessor.
   * Retrieve the reference by index.
   */
  value_t& get( index_t row, index_t column )
  {
    if( this->is_transposed ) {
      std::swap( row, column );
    }
    
    index_t index = ( row * this->columns + column );
    
    return this->values[ index ];
  }



  /**
   * A const private accessor.
   * Retrieve the const reference by index.
   */
  const value_t& get( index_t row, index_t column ) const
  {
    if( this->is_transposed ) {
      std::swap( row, column );
    }
    
    index_t index = ( row * this->columns + column );
    
    return this->values[ index ];
  }



  std::valarray< value_t > values;  /**< A storage for matrix elements. */
  index_t rows;                     /**< A number of rows. */
  index_t columns;                  /**< A number of columns. */

  bool is_transposed;               /**< A transposition flag. */
};



#endif // MATRIX
