#ifndef MATRIX_H
#define MATRIX_H

#include <mutex>
#include <valarray>
#include <assert.h>

// Represents matrix
template< typename T >
class Matrix
{
private:
  typedef std::size_t Index;
  typedef std::lock_guard< std::mutex > Lock;

public:

  // Constructs a rows-by-columns Matrix with each element initialized to the given value
  Matrix( Index rows, Index columns, const T& initializer = T( 0 ) )
  {
    Lock lock( this->mutex );
    
    assert( rows > 0 );
    assert( columns > 0 );
    
    this->elements = std::valarray< T >( initializer, rows * columns );
    this->rows = rows;
    this->columns = columns;
  }



  // Constructs a Matrix from the existed matrix by copying elements
  Matrix( const Matrix< T >& rhs )
  {
    std::lock( this->mutex, rhs.mutex );
    Lock lock_myself( this->mutex, std::adopt_lock );
    Lock lock_rhs( rhs.mutex, std::adopt_lock );
    
    this->elements = rhs.elements;
    this->rows = rhs.rows;
    this->columns = rhs.columns;
  }



  // Constructs a Matrix from the existed matrix by moving elements
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
    Lock lock( this->mutex );

    assert( row < this->rows );
    assert( column < this->columns );
    
    Index index = row * this->columns + column;
    return this->elements[ index ];
  }
  
  
  
  // Retrieves a const reference
  const T& operator() ( Index row, Index column ) const
  {
    Lock lock( this->mutex );

    assert( row < this->rows );
    assert( column < this->columns );
    
    Index index = row * this->columns + column;
    return this->elements[ index ];
  }
  
  
  
  // Copy-based assignment
  Matrix< T >& operator= ( const Matrix< T >& rhs );
  
  // Move-based assignment
  Matrix< T >& operator= ( const Matrix< T >&& rhs );
  
  // Matrix operations
  Matrix< T >& operator+ ( const Matrix< T >& rhs );
  Matrix< T >& operator- ( const Matrix< T >& rhs );
  Matrix< T >& operator* ( const Matrix< T >& rhs );



  // Comparison operator
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
