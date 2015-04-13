#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <mutex>
#include <valarray>

#include "ParallelHandler.h"



template< typename T >
class Matrix
{
private:

  typedef std::size_t Index;
  typedef std::lock_guard< std::mutex > Lock;

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
  {
    Lock lock_rhs( rhs.mutex );
    
    this->elements = rhs.elements;
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->isTransposed = rhs.isTransposed;
  }



  // Construct a copy using resources of temporary Matrix object
  Matrix( const Matrix< T >&& rhs )
    : elements( std::move( rhs.elements ) )
    , rows( rhs.rows )
    , columns( rhs.columns )
    , isTransposed( rhs.isTransposed )
  {

  }



  // Retrieve the reference
  T& operator() ( Index row, Index column )
  {    
    assert( row < this->get_rows() );
    assert( column < this->get_columns() );
    
    Lock lock( this->mutex );
    
    return this->get_nonblock( row, column );
  }



  // Retrieve the const reference
  const T& operator() ( Index row, Index column ) const
  {    
    assert( row < this->get_rows() );
    assert( column < this->get_columns() );
    
    Lock lock( this->mutex );
    
    return this->get_nonblock( row, column );
  }



  // Make the matrix equal to other Matrix object
  Matrix< T >& operator= ( const Matrix< T >& rhs )
  {
    if( this == &rhs ) {
      return *this;
    }
        
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
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
    
    Lock lock_myself( this->mutex, std::adopt_lock );
    
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
    
    auto summarize = [ this, &rhs, &result ]( const Index& iRowStart, const Index& iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < this->get_columns_nonblock(); ++jColumn ) {
          result.get_nonblock( iRow, jColumn ) = (
            this->get_nonblock( iRow, jColumn ) + rhs.get_nonblock( iRow, jColumn ) 
          );
        }
      }
    };
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    Index first = 0;
    Index last = this->get_rows_nonblock();
    this->parallelHandler.loop_for( first, last, summarize );
        
    return result;
  }



  // Retrieve the Matrix each element of which is the difference of the corresponding
  // elements of this and rhs Matrix objects
  Matrix< T > operator- ( const Matrix< T >& rhs ) const
  {
    assert( this->get_rows() == rhs.get_rows() );
    assert( this->get_columns() == rhs.get_columns() );
    
    Matrix< T > result( this->get_rows(), this->get_columns() );
    
    auto subtract = [ this, &rhs, &result ]( Index iRowStart, Index iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < this->get_columns_nonblock(); ++jColumn ) {
          result.get_nonblock( iRow, jColumn ) = (
            this->get_nonblock( iRow, jColumn ) - rhs.get_nonblock( iRow, jColumn )
          );
        }
      }
    };
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    Index first = 0;
    Index last = this->get_rows_nonblock();
    this->parallelHandler.loop_for( first, last, subtract );
        
    return result;
  }



  // Retrieve the Matrix which is equal to result of matrix multiplication
  // of this and rhs Matrix objects
  Matrix< T > operator* ( const Matrix< T >& rhs )
  {
    assert( this->get_columns() == rhs.get_rows() );
    
    Matrix< T > result( this->get_rows(), rhs.get_columns() );
    
    auto multiply = [ this, &rhs, &result ]( Index iRowStart, Index iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < rhs.get_columns_nonblock(); ++jColumn ) {
          for( Index sIndex = 0; sIndex < this->get_columns_nonblock(); ++sIndex ) {
            result.get_nonblock( iRow, jColumn ) += (
              this->get_nonblock( iRow, sIndex ) * rhs.get_nonblock( sIndex, jColumn )
            );
          }
        }
      }
    };
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    Index first = 0;
    Index last = this->get_rows_nonblock();
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
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
        
    bool rowsMismatch = ( this->get_rows_nonblock() != rhs.get_rows_nonblock() );
    bool columnsMismatch = ( this->get_columns_nonblock() != rhs.get_columns_nonblock() );
    
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
    Lock lock( this->mutex );
        
    return this->get_rows_nonblock();
  }



  // Retrieve the number of columns of the matrix
  Index get_columns() const
  {
    Lock lock( this->mutex );
    
    return this->get_columns_nonblock();
  }



private:

  // Retrieve the number of rows of the matrix without using a mutex lock
  Index get_rows_nonblock() const
  {
    return ( this->isTransposed ? this->columns : this->rows );
  }



  // Retrieve the number of columns of the matrix without using a mutex lock
  Index get_columns_nonblock() const
  {
    return ( this->isTransposed ? this->rows : this->columns );
  }



  // Retrieve the reference by index without using a mutex lock
  T& get_nonblock( Index row, Index column )
  {
    if( this->isTransposed ) {
      std::swap( row, column );
    }
    
    Index index = ( row * this->columns + column );
    
    return this->elements[ index ];
  }



  // Retrieve the const reference by index without using a mutex lock
  const T& get_nonblock( Index row, Index column ) const
  {
    if( this->isTransposed ) {
      std::swap( row, column );
    }
    
    Index index = ( row * this->columns + column );
    
    return this->elements[ index ];
  }


  
  template< typename D >
  friend Matrix< D >& operator* ( const D& value, Matrix< D >& rhs );

#ifdef TIME_TEST
  friend class MatrixMultiplier;
  friend class MatrixRandomFiller;
  friend class MatrixSummarizer;
#endif // TIME_TEST


  mutable ParallelHandler parallelHandler;
  mutable std::mutex mutex;
    
  std::valarray< T > elements;
  Index rows;
  Index columns;
  
  bool isTransposed;
};



// Multiply each element of the rhs by value
template< typename T >
Matrix< T >& operator* ( const T& value , Matrix< T >& rhs )
{
  auto multiply = [ &rhs, &value ]( typename Matrix< T >::Index iRowStart, typename Matrix< T >::Index iRowEnd ) -> void
  {
    for( typename Matrix< T >::Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
      for( typename Matrix< T >::Index jColumn = 0; jColumn < rhs.get_columns_nonblock(); ++jColumn ) {
        rhs.get_nonblock( iRow, jColumn ) *= value;
      }
    }
  };
  
  typename Matrix< T >::Lock lock( rhs.mutex );
  
  typename Matrix< T >::Index first = 0;
  typename Matrix< T >::Index last = rhs.get_rows_nonblock();
  rhs.parallelHandler.loop_for( first, last, multiply );
  
  return rhs;
}



#endif // MATRIX_H
