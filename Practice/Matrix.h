#ifndef MATRIX_H
#define MATRIX_H

#include <mutex>
#include <valarray>
#include <assert.h>

#include <iostream>



// Represents a matrix
template< typename T >
class Matrix
{
private:
  typedef std::size_t Index;
  typedef std::lock_guard< std::mutex > Lock;

public:

  // Constructs a rows-by-columns Matrix with each element initialized to the given value
  Matrix( Index rows, Index columns, const T& val = T( 0 ) )
  {
    assert( rows > 0 );
    assert( columns > 0 );
    
    Lock lock( this->mutex );
        
    this->elements = std::valarray< T >( val, rows * columns );
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



  // Retrieves a reference
  T& operator() ( Index row, Index column )
  {
    assert( row < this->rows );
    assert( column < this->columns );
    
    Lock lock( this->mutex );
    
    Index index = row * this->columns + column;
    
    return this->elements[ index ];
  }
  
  
  
  // Retrieves a const reference
  const T& operator() ( Index row, Index column ) const
  {
    assert( row < this->rows );
    assert( column < this->columns );
    
    Lock lock( this->mutex );
    
    Index index = row * this->columns + column;
    
    return this->elements[ index ];
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



  Matrix< T > operator* ( const Matrix< T >& rhs )
  {
    assert( this->columns == rhs.rows );
    
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    Matrix< T > result( this->rows, rhs.columns );
        
    for( Index iRow = 0; iRow < this->rows; ++iRow ) {
      for ( Index iColumn = 0; iColumn < rhs.columns; ++iColumn ) {
        std::size_t start = iRow;
        std::size_t length = this->columns;
        std::size_t stride = 1;
        std::slice row( start, length, stride );
    
        start = iColumn;
        length = rhs.rows;
        stride = rhs.columns;
        std::slice column( start, length, stride );
    
        std::valarray< T > multiplication_result = this->elements[ row ] * rhs.elements[ column ];
        result.elements = multiplication_result.sum();
        
        break;
      }
      
      break;
    }
    
    return result;
  }



  bool operator== ( const Matrix< T >& rhs ) const
  {
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    if ( &rhs == this ) {
      return true;
    }
    
    bool rowsMismatch = ( this->rows != rhs.rows );
    bool columnsMismatch = ( this->columns != rhs.columns );
    
    if ( rowsMismatch || columnsMismatch ) {
      return false;
    }
    
    std::valarray< bool > comp = ( this->elements == rhs.elements );
    bool isEqual = ( comp.min() == true );
    
    return isEqual;
  }



  // Retrieves negate result of comparison operator
  bool operator!= ( const Matrix< T >& rhs ) const
  {
    return !( *this == rhs );
  }
  
  
  
  // Transpose the matrix  
  Matrix< T >& transpose();



  // Retrieves number of rows
  Index get_rows() const
  {
    Lock lock( this->mutex );
    return this->rows;
  }



  // Retrieves number of columns
  Index get_columns() const
  {
    Lock lock( this->mutex );
    return this->columns;
  }

private:
  mutable std::mutex mutex;
  std::valarray< T > elements;
  Index rows;
  Index columns;
};



// Non-member functions

// Scalar multiplication
template< typename T >
Matrix< T >& operator* ( const T& value , Matrix< T >& rhs )
{
  // TODO: scalar multiplication
}



#endif // MATRIX_H
