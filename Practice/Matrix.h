#ifndef MATRIX_H
#define MATRIX_H

#include <mutex>
#include <thread>
#include <valarray>
#include <vector>
#include <assert.h>



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
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    Matrix< T > result( this->rows, this->columns );
    
    result.elements = this->elements + rhs.elements;
    
    return result;
  }



  Matrix< T > operator- ( const Matrix< T >& rhs ) const
  {
    assert( this->rows == rhs.rows );
    assert( this->columns == rhs.columns );
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    Matrix< T > result( this->rows, this->columns );
    
    result.elements = this->elements - rhs.elements;
    
    return result;
  }



  Matrix< T > operator* ( const Matrix< T >& rhs )
  {
    assert( this->columns == rhs.rows );
    
    const uint64_t length = this->rows;
    const uint64_t minRowsPerThread = 25; 
    const uint64_t maxThreads = ( length + minRowsPerThread - 1 ) / minRowsPerThread;
    const uint64_t hardwareThreads = std::thread::hardware_concurrency();
    const uint64_t nThreads = std::min( ( hardwareThreads == 0 ? 2 : hardwareThreads ), maxThreads );
    const uint64_t blockSize = length / nThreads;

    Matrix< T > result( this->rows, rhs.columns );
    std::vector< std::thread > threads( nThreads - 1 );
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    auto calculateBlock = [ this, &rhs, &result ]( Index iRowStart, Index iRowEnd ) -> void
    {
      for( Index iRow = iRowStart; iRow < iRowEnd; ++iRow ) {
        for( Index jColumn = 0; jColumn < rhs.columns; ++jColumn ) {
          for( Index sIndex = 0; sIndex < this->columns; ++sIndex ) {
            result( iRow, jColumn ) += this->get( iRow, sIndex ) * rhs.get( sIndex, jColumn );
          }
        }
      }
    };
    
    Index iRowStart = 0;
    for( uint64_t iThread = 0; iThread < (nThreads - 1); ++iThread ) {
      Index iRowEnd = iRowStart;
      iRowEnd += blockSize;
      threads[ iThread ] = std::thread( calculateBlock, iRowStart, iRowEnd );
      iRowStart = iRowEnd;
    }
    
    calculateBlock( iRowStart, this->rows );
    
    std::for_each( threads.begin(), threads.end(), std::mem_fn( &std::thread::join ) );
    
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
    Lock lock( this->mutex );
    
    Matrix< T > result( this->columns, this->rows );
    
    for( Index iRow = 0; iRow < this->rows; ++iRow ) {
      for( Index jColumn = 0; jColumn < this->columns; ++jColumn ) {
        result.get( jColumn, iRow ) = this->get( iRow, jColumn );
      }
    }
    
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



  mutable std::mutex mutex;
  std::valarray< T > elements;
  Index rows;
  Index columns;
};



// Scalar multiplication
template< typename T >
Matrix< T >& operator* ( const T& value , Matrix< T >& rhs )
{
  for( std::size_t iRow = 0; iRow < rhs.get_rows(); ++iRow ) {
    for( std::size_t jColumn = 0; jColumn < rhs.get_columns(); ++jColumn ) {
      rhs( iRow, jColumn ) *= value;
    }
  }
  
  return rhs;
}



#endif // MATRIX_H
