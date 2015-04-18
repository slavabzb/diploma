#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <valarray>

#include "ParallelHandler.h"



template< typename T >
class Matrix
{
private:

  typedef std::size_t Index;



public:

  // Construct a rows-by-columns Matrix filled with the given value
  Matrix( Index rows, Index columns, const T& value = T( 0 ) )
    : elements( value, rows * columns )
    , rows( rows )
    , columns( columns )
    , isTransposed( false )
  {
    assert( rows > 0 );
    assert( columns > 0 );
  }



  // Construct a copy of other Matrix object
  Matrix( const Matrix< T >& rhs )
    : elements( rhs.elements )
    , rows( rhs.rows )
    , columns( rhs.columns )
    , isTransposed( rhs.isTransposed )
  {

  }



  // Construct a copy using resources of temporary Matrix object
  Matrix( Matrix< T >&& rhs )
    : elements( std::move( rhs.elements ) )
    , rows( rhs.rows )
    , columns( rhs.columns )
    , isTransposed( rhs.isTransposed )
  {

  }



  // Retrieve the reference
  T& operator() ( const Index& row, const Index& column )
  {    
    assert( row < this->get_rows() );
    assert( column < this->get_columns() );

    return this->get( row, column );
  }



  // Retrieve the const reference
  const T& operator() ( const Index& row, const Index& column ) const
  {    
    assert( row < this->get_rows() );
    assert( column < this->get_columns() );

    return this->get( row, column );
  }



  // Make the matrix equal to other Matrix object
  Matrix< T >& operator= ( const Matrix< T >& rhs )
  {
    if( this == &rhs ) {
      return *this;
    }

    this->elements = rhs.elements;
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->isTransposed = rhs.isTransposed;

    return *this;
  }



  // Make the matrix the owner of the resources of the temporary Matrix object
  Matrix< T >& operator= ( Matrix< T >&& rhs )
  {
    if (this == &rhs) {
      return *this;
    }

    this->elements = std::move( rhs.elements );
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->isTransposed = rhs.isTransposed;

    return *this;
  }



  // Retrieve the Matrix each element of which is the sum of the corresponding
  // elements of this and rhs Matrix objects
  Matrix< T > operator+ ( const Matrix< T >& rhs ) const
  {
    assert( this->get_rows() == rhs.get_rows() );
    assert( this->get_columns() == rhs.get_columns() );
    
    Matrix< T > result( this->get_rows(), this->get_columns() );
    
    auto summarize = [ this, &rhs, &result ]( const Index& iRowStart,
      const Index& iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < this->get_columns(); ++jColumn ) {
          result.get( iRow, jColumn ) = (
            this->get( iRow, jColumn ) + rhs.get( iRow, jColumn ) 
          );
        }
      }
    };

    const std::size_t prev = this->parallelHandler.getMinPerThread();
    this->parallelHandler.setMinPerThread( 10 * prev );

    const Index first = 0;
    const Index last = this->get_rows();
    this->parallelHandler.loop_for( first, last, summarize );

    this->parallelHandler.setMinPerThread( prev );

    return result;
  }



  // Retrieve the Matrix each element of which is the difference of the corresponding
  // elements of this and rhs Matrix objects
  Matrix< T > operator- ( const Matrix< T >& rhs ) const
  {
    assert( this->get_rows() == rhs.get_rows() );
    assert( this->get_columns() == rhs.get_columns() );
    
    Matrix< T > result( this->get_rows(), this->get_columns() );
    
    auto subtract = [ this, &rhs, &result ]( const Index& iRowStart,
      const Index& iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < this->get_columns(); ++jColumn ) {
          result.get( iRow, jColumn ) = (
            this->get( iRow, jColumn ) - rhs.get( iRow, jColumn )
          );
        }
      }
    };

    const Index first = 0;
    const Index last = this->get_rows();
    this->parallelHandler.loop_for( first, last, subtract );

    return result;
  }



  // Retrieve the Matrix which is equal to result of matrix multiplication
  // of this and rhs Matrix objects
  Matrix< T > operator* ( const Matrix< T >& rhs )
  {
    assert( this->get_columns() == rhs.get_rows() );
    
    Matrix< T > result( this->get_rows(), rhs.get_columns() );
    
    auto multiply = [ this, &rhs, &result ]( const Index& iRowStart,
      const Index& iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < rhs.get_columns(); ++jColumn ) {
          for( Index sIndex = 0; sIndex < this->get_columns(); ++sIndex ) {
            result.get( iRow, jColumn ) += (
              this->get( iRow, sIndex ) * rhs.get( sIndex, jColumn )
            );
          }
        }
      }
    };

    const Index first = 0;
    const Index last = this->get_rows();
    this->parallelHandler.loop_for( first, last, multiply );

    return result;
  }



  // Check if each element of the matrix is equal to the corresponding
  // element of the other Matrix object
  bool operator== ( const Matrix< T >& rhs ) const
  {
    if ( &rhs == this ) {
      return true;
    }

    bool rowsMismatch = ( this->get_rows() != rhs.get_rows() );
    bool columnsMismatch = ( this->get_columns() != rhs.get_columns() );
    
    if ( rowsMismatch || columnsMismatch ) {
      return false;
    }
    
    std::valarray< bool > comp = ( this->elements == rhs.elements );
    bool isEqual = ( comp.min() == true );
    
    return isEqual;
  }



  // Check if the matrix is not equal to the other Matrix object
  bool operator!= ( const Matrix< T >& rhs ) const
  {
    return !( *this == rhs );
  }



  // Swap rows and columns
  Matrix< T >& transpose()
  {    
    this->isTransposed = !this->isTransposed;
    
    return *this;
  }



  // Retrieve the number of rows of the matrix
  Index get_rows() const
  {
    return ( this->isTransposed ? this->columns : this->rows );
  }



  // Retrieve the number of columns of the matrix
  Index get_columns() const
  {
    return ( this->isTransposed ? this->rows : this->columns );
  }



private:

  // Retrieve the reference by index
  T& get( Index row, Index column )
  {
    if( this->isTransposed ) {
      std::swap( row, column );
    }
    
    Index index = ( row * this->columns + column );
    
    return this->elements[ index ];
  }



  // Retrieve the const reference by index
  const T& get( Index row, Index column ) const
  {
    if( this->isTransposed ) {
      std::swap( row, column );
    }
    
    Index index = ( row * this->columns + column );
    
    return this->elements[ index ];
  }



  template< typename D >
  friend Matrix< D >& operator* ( const D& value , Matrix< D >& rhs );



  mutable ParallelHandler parallelHandler;
    
  std::valarray< T > elements;
  Index rows;
  Index columns;

  bool isTransposed;
};



// Multiply each element of the Matrix by value
template< typename T >
Matrix< T >& operator* ( const T& value , Matrix< T >& rhs )
{
  using Index = typename Matrix< T >::Index;

  auto multiply = [ &rhs, &value ]( const Index& iRowStart,
    const Index& iRowEnd ) -> void
  {
    for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
      for( Index jColumn = 0; jColumn < rhs.get_columns(); ++jColumn ) {
        rhs.get( iRow, jColumn ) *= value;
      }
    }
  };

  const Index first = 0;
  const Index last = rhs.get_rows();
  rhs.parallelHandler.loop_for( first, last, multiply );
  
  return rhs;
}



#endif // MATRIX_H
