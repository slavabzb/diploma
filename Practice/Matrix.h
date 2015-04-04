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
  }



  Matrix( const Matrix< T >& rhs )
  {
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    this->elements = rhs.elements;
    this->rows = rhs.rows;
    this->columns = rhs.columns;
  }



  Matrix( const Matrix< T >&& rhs )
  {
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    this->elements = std::move( rhs.elements );
    this->rows = rhs.rows;
    this->columns = rhs.columns;
  }



  T& operator() ( Index row, Index column )
  {
    assert( row < this->rows );
    assert( column < this->columns );
    
    Lock lock( this->mutex );
    
    return this->get( row, column );
  }
  
  
  
  const T& operator() ( Index row, Index column ) const
  {
    assert( row < this->rows );
    assert( column < this->columns );
    
    Lock lock( this->mutex );
    
    return this->get( row, column );
  }



  Matrix< T >& operator= ( const Matrix< T >& rhs )
  {
    if (this == &rhs) {
      return *this;
    }
        
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    this->elements = rhs.elements;    
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    
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
    
    return *this;
  }
  


  Matrix< T > operator+ ( const Matrix< T >& rhs ) const
  {
    assert( this->rows == rhs.rows );
    assert( this->columns == rhs.columns );
    
    Matrix< T > result( this->rows, this->columns );
    
    auto summarize = [ this, &rhs, &result ]( const Index& iRowStart, const Index& iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < this->columns; ++jColumn ) {
          result.get( iRow, jColumn ) = this->get( iRow, jColumn ) + rhs.get( iRow, jColumn );
        }
      }
    };
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    Index first = 0;
    Index last = this->rows;
    this->parallelHandler.loop_for( first, last, summarize );
        
    return result;
  }



  Matrix< T > operator- ( const Matrix< T >& rhs ) const
  {
    assert( this->rows == rhs.rows );
    assert( this->columns == rhs.columns );
    
    Matrix< T > result( this->rows, this->columns );
    
    auto subtract = [ this, &rhs, &result ]( Index iRowStart, Index iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < this->columns; ++jColumn ) {
          result.get( iRow, jColumn ) = this->get( iRow, jColumn ) - rhs.get( iRow, jColumn );
        }
      }
    };
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    Index first = 0;
    Index last = this->rows;
    this->parallelHandler.loop_for( first, last, subtract );
        
    return result;
  }


  
  Matrix< T > operator* ( const Matrix< T >& rhs )
  {
    assert( this->columns == rhs.rows );
    
    Matrix< T > result( this->rows, rhs.columns );
    
    auto multiply = [ this, &rhs, &result ]( Index iRowStart, Index iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < rhs.columns; ++jColumn ) {
          for( Index sIndex = 0; sIndex < this->columns; ++sIndex ) {
            result.get( iRow, jColumn ) += this->get( iRow, sIndex ) * rhs.get( sIndex, jColumn );
          }
        }
      }
    };
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    Index first = 0;
    Index last = this->rows;
    this->parallelHandler.loop_for( first, last, multiply );
    
    return result;
  }



  Matrix< T >& operator+= ( const Matrix< T >& rhs )
  {
    *this = *this + rhs;
    
    return *this;
  }



  Matrix< T >& operator-= ( const Matrix< T >& rhs )
  {
    *this = *this - rhs;
    
    return *this;
  }
  
  
  
  Matrix< T >& operator*= ( const Matrix< T >& rhs )
  {
    *this = *this * rhs;
    
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
        
    bool rowsMismatch = ( this->rows != rhs.rows );
    bool columnsMismatch = ( this->columns != rhs.columns );
    
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
  
  
    
  Matrix< T > transpose() const
  {    
    Matrix< T > result( this->columns, this->rows );  
    
    auto swap = [ this, &result ]( Index iRowStart, Index iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < this->columns; ++jColumn ) {
          result.get( jColumn, iRow ) = this->get( iRow, jColumn );
        }
      }
    };
    
    Lock lock( this->mutex );
    
    Index first = 0;
    Index last = this->rows;
    this->parallelHandler.loop_for( first, last, swap );  
    
    return result;
  }



  Index get_rows() const
  {
    Lock lock( this->mutex );
    
    return this->rows;
  }



  Index get_columns() const
  {
    Lock lock( this->mutex );
    
    return this->columns;
  }



private:

  T& get( Index row, Index column )
  {
    Index index = row * this->columns + column;
    
    return this->elements[ index ];
  }



  const T& get( Index row, Index column ) const
  {
    Index index = row * this->columns + column;
    
    return this->elements[ index ];
  }


  
  template< typename D >
  friend Matrix< D >& operator* ( const D& value , Matrix< D >& rhs );



  mutable ParallelHandler parallelHandler;
  mutable std::mutex mutex;
  
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
      for( typename Matrix< T >::Index jColumn = 0; jColumn < rhs.columns; ++jColumn ) {
        rhs.get( iRow, jColumn ) *= value;
      }
    }
  };
  
  typename Matrix< T >::Lock lock( rhs.mutex );
  
  typename Matrix< T >::Index first = 0;
  typename Matrix< T >::Index last = rhs.rows;
  rhs.parallelHandler.loop_for( first, last, multiply );
  
  return rhs;
}



#endif // MATRIX_H
