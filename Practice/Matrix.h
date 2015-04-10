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

  Matrix( Index rows, Index columns, const T& value = T( 0 ) )
  {
    assert( rows > 0 );
    assert( columns > 0 );
    
    Lock lock( this->mutex );
        
    this->elements = std::valarray< T >( value, rows * columns );
    this->rows = rows;
    this->columns = columns;
    this->isTransposed = false;
  }



  Matrix( const Matrix< T >& rhs )
  {
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    this->elements = rhs.elements;
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->isTransposed = rhs.isTransposed;
  }



  Matrix( const Matrix< T >&& rhs )
  {
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    this->elements = std::move( rhs.elements );
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->isTransposed = rhs.isTransposed;
  }



  T& operator() ( Index row, Index column )
  {    
    assert( row < this->get_rows() );
    assert( column < this->get_columns() );
    
    Lock lock( this->mutex );
    
    return this->get_nonblock( row, column );
  }
  
  
  
  const T& operator() ( Index row, Index column ) const
  {    
    assert( row < this->get_rows() );
    assert( column < this->get_columns() );
    
    Lock lock( this->mutex );
    
    return this->get_nonblock( row, column );
  }



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



  Matrix< T >& operator= ( const Matrix< T >&& rhs )
  {
    if (this == &rhs) {
      return *this;
    }
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    this->elements = std::move( rhs.elements );
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->isTransposed = rhs.isTransposed;
    
    return *this;
  }
  


  Matrix< T > operator+ ( const Matrix< T >& rhs ) const
  {
    assert( this->get_rows() == rhs.get_rows() );
    assert( this->get_columns() == rhs.get_columns() );
    
    Matrix< T > result( this->get_rows(), this->get_columns() );
    
    auto summarize = [ this, &rhs, &result ]( const Index& iRowStart, const Index& iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < this->columns; ++jColumn ) {
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



  Matrix< T > operator- ( const Matrix< T >& rhs ) const
  {
    assert( this->get_rows() == rhs.get_rows() );
    assert( this->get_columns() == rhs.get_columns() );
    
    Matrix< T > result( this->get_rows(), this->get_columns() );
    
    auto subtract = [ this, &rhs, &result ]( Index iRowStart, Index iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < this->columns; ++jColumn ) {
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



  Matrix< T >& operator+= ( const Matrix< T >& rhs )
  {
    *this = ( *this + rhs );
    
    return *this;
  }



  Matrix< T >& operator-= ( const Matrix< T >& rhs )
  {
    *this = ( *this - rhs );
    
    return *this;
  }
  
  
  
  Matrix< T >& operator*= ( const Matrix< T >& rhs )
  {
    *this = ( *this * rhs );
    
    return *this;
  }
  
  

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



  bool operator!= ( const Matrix< T >& rhs ) const
  {
    return !( *this == rhs );
  }
  
  
    
  Matrix< T >& transpose()
  {    
    this->isTransposed = !this->isTransposed;
    
    return *this;
  }



  Index get_rows() const
  {
    Lock lock( this->mutex );
        
    return this->get_rows_nonblock();
  }



  Index get_columns() const
  {
    Lock lock( this->mutex );
    
    return this->get_columns_nonblock();
  }
  
  
  
private:

  Index get_rows_nonblock() const
  {
    return ( this->isTransposed ? this->columns : this->rows );
  }



  Index get_columns_nonblock() const
  {
    return ( this->isTransposed ? this->rows : this->columns );
  }



  T& get_nonblock( Index row, Index column )
  {
    if( this->isTransposed ) {
      std::swap( row, column );
    }
    
    Index index = row * this->columns + column;
    
    return this->elements[ index ];
  }



  const T& get_nonblock( Index row, Index column ) const
  {
    if( this->isTransposed ) {
      std::swap( row, column );
    }
    
    Index index = row * this->columns + column;
    
    return this->elements[ index ];
  }


  
  template< typename D >
  friend Matrix< D >& operator* ( const D& value , Matrix< D >& rhs );

#ifdef TIME_TEST
  friend class MatrixMultiplier;
  friend class MatrixSummarizer;
#endif // TIME_TEST


  mutable ParallelHandler parallelHandler;
  mutable std::mutex mutex;
  
  bool isTransposed;
  
  std::valarray< T > elements;
  Index rows;
  Index columns;
};



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
