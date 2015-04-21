#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <valarray>

#include "ParallelHandler.h"



template< typename T >
class Matrix
{
private:

  typedef T value_t;
  typedef Matrix< value_t > my_t;
  typedef std::size_t index_t;



public:

  // Construct a rows-by-columns Matrix filled with the given value
  Matrix( index_t rows, index_t columns, const value_t& value = value_t( 0 ) )
    : values( value, rows * columns )
    , rows( rows )
    , columns( columns )
    , isTransposed( false )
  {
    assert( rows > 0 );
    assert( columns > 0 );
  }



  // Construct a copy of other Matrix object
  Matrix( const my_t& rhs )
    : values( rhs.values )
    , rows( rhs.rows )
    , columns( rhs.columns )
    , isTransposed( rhs.isTransposed )
  {

  }



  // Construct a copy using resources of temporary Matrix object
  Matrix( my_t&& rhs )
    : values( std::move( rhs.values ) )
    , rows( rhs.rows )
    , columns( rhs.columns )
    , isTransposed( rhs.isTransposed )
  {

  }



  // Retrieve the reference
  value_t& operator() ( const index_t& row, const index_t& column )
  {    
    assert( row < this->get_rows() );
    assert( column < this->get_columns() );

    return this->get( row, column );
  }



  // Retrieve the const reference
  const value_t& operator() ( const index_t& row, const index_t& column ) const
  {    
    assert( row < this->get_rows() );
    assert( column < this->get_columns() );

    return this->get( row, column );
  }



  // Make the matrix equal to other Matrix object
  my_t& operator= ( const my_t& rhs )
  {
    if( this == &rhs ) {
      return *this;
    }

    this->values = rhs.values;
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->isTransposed = rhs.isTransposed;

    return *this;
  }



  // Make the matrix the owner of the resources of the temporary Matrix object
  my_t& operator= ( my_t&& rhs )
  {
    if (this == &rhs) {
      return *this;
    }

    this->values = std::move( rhs.values );
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->isTransposed = rhs.isTransposed;

    return *this;
  }



  // Retrieve the Matrix each element of which is the sum of the corresponding
  // values of this and rhs Matrix objects
  my_t operator+ ( const my_t& rhs ) const
  {
    assert( this->get_rows() == rhs.get_rows() );
    assert( this->get_columns() == rhs.get_columns() );
    
    my_t result( this->get_rows(), this->get_columns() );
    
    auto summarize = [ this, &rhs, &result ]( const index_t& iRowStart,
      const index_t& iRowEnd ) -> void
    {
      for( index_t iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( index_t jColumn = 0; jColumn < this->get_columns(); ++jColumn ) {
          result.get( iRow, jColumn ) = (
            this->get( iRow, jColumn ) + rhs.get( iRow, jColumn ) 
          );
        }
      }
    };

    const index_t first = 0;
    const index_t last = this->get_rows();
    my_t::getParallelHandler()->loop_for( first, last, summarize );

    return result;
  }



  // Retrieve the Matrix each element of which is the difference of the corresponding
  // values of this and rhs Matrix objects
  my_t operator- ( const my_t& rhs ) const
  {
    assert( this->get_rows() == rhs.get_rows() );
    assert( this->get_columns() == rhs.get_columns() );
    
    my_t result( this->get_rows(), this->get_columns() );
    
    auto subtract = [ this, &rhs, &result ]( const index_t& iRowStart,
      const index_t& iRowEnd ) -> void
    {
      for( index_t iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( index_t jColumn = 0; jColumn < this->get_columns(); ++jColumn ) {
          result.get( iRow, jColumn ) = (
            this->get( iRow, jColumn ) - rhs.get( iRow, jColumn )
          );
        }
      }
    };

    const index_t first = 0;
    const index_t last = this->get_rows();
    my_t::getParallelHandler()->loop_for( first, last, subtract );

    return result;
  }



  // Retrieve the Matrix which is equal to result of matrix multiplication
  // of this and rhs Matrix objects
  my_t operator* ( const my_t& rhs ) const
  {
    assert( this->get_columns() == rhs.get_rows() );
    
    my_t result( this->get_rows(), rhs.get_columns() );
    
    auto multiply = [ this, &rhs, &result ]( const index_t& iRowStart,
      const index_t& iRowEnd ) -> void
    {
      for( index_t iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( index_t jColumn = 0; jColumn < rhs.get_columns(); ++jColumn ) {
          for( index_t sIndex = 0; sIndex < this->get_columns(); ++sIndex ) {
            result.get( iRow, jColumn ) += (
              this->get( iRow, sIndex ) * rhs.get( sIndex, jColumn )
            );
          }
        }
      }
    };

    const index_t first = 0;
    const index_t last = this->get_rows();
    my_t::getParallelHandler()->loop_for( first, last, multiply );

    return result;
  }



  // Check if each element of the matrix is equal to the corresponding
  // element of the other Matrix object
  bool operator== ( const my_t& rhs ) const
  {
    if ( &rhs == this ) {
      return true;
    }

    bool rowsMismatch = ( this->get_rows() != rhs.get_rows() );
    bool columnsMismatch = ( this->get_columns() != rhs.get_columns() );
    
    if ( rowsMismatch || columnsMismatch ) {
      return false;
    }
    
    std::valarray< bool > comp = ( this->values == rhs.values );
    bool isEqual = ( comp.min() == true );
    
    return isEqual;
  }



  // Check if the matrix is not equal to the other Matrix object
  bool operator!= ( const my_t& rhs ) const
  {
    return !( *this == rhs );
  }



  // Swap rows and columns
  my_t& transpose()
  {    
    this->isTransposed = !this->isTransposed;
    
    return *this;
  }



  // Retrieve the number of rows of the matrix
  index_t get_rows() const
  {
    return ( this->isTransposed ? this->columns : this->rows );
  }



  // Retrieve the number of columns of the matrix
  index_t get_columns() const
  {
    return ( this->isTransposed ? this->rows : this->columns );
  }



  // Retrieve an instance of parallel execution controller
  static ParallelHandler* getParallelHandler()
  {
    static ParallelHandler parallelHandler;

    return &parallelHandler;
  }



private:

  // Retrieve the reference by index
  value_t& get( index_t row, index_t column )
  {
    if( this->isTransposed ) {
      std::swap( row, column );
    }
    
    index_t index = ( row * this->columns + column );
    
    return this->values[ index ];
  }



  // Retrieve the const reference by index
  const value_t& get( index_t row, index_t column ) const
  {
    if( this->isTransposed ) {
      std::swap( row, column );
    }
    
    index_t index = ( row * this->columns + column );
    
    return this->values[ index ];
  }



  template< typename D >
  friend Matrix< D >& operator* ( const D& value , Matrix< D >& rhs );



  std::valarray< value_t > values;
  index_t rows;
  index_t columns;

  bool isTransposed;
};



// Multiply each element of the Matrix by value
template< typename T >
Matrix< T >& operator* ( const T& value , Matrix< T >& rhs )
{
  using index_t = typename Matrix< T >::index_t;

  auto multiply = [ &rhs, &value ]( const index_t& iRowStart,
    const index_t& iRowEnd ) -> void
  {
    for( index_t iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
      for( index_t jColumn = 0; jColumn < rhs.get_columns(); ++jColumn ) {
        rhs.get( iRow, jColumn ) *= value;
      }
    }
  };

  const index_t first = 0;
  const index_t last = rhs.get_rows();
  Matrix< T >::getParallelHandler()->loop_for( first, last, multiply );
  
  return rhs;
}



#endif // MATRIX_H
