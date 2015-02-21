#ifndef MATRIX_H
#define MATRIX_H

#include <mutex>
#include <valarray>

// Represents matrix
template< typename T >
class Matrix
{
private:
  typedef std::size_t Index;
  typedef std::lock_guard< std::mutex > LockGuard;

public:

  // Constructs a rows-by-columns Matrix with each element initialized to the initializer value
  Matrix( Index rows, Index columns, const T& initializer = T( 0 ) )
  {
    LockGuard lock( this->mutex );
    this->elements = std::valarray< T >( rows * columns, initializer );
    this->rows = rows;
    this->columns = columns;
  }



  // Constructs a Matrix from the matrix by copying elements
  Matrix( const Matrix< T >& matrix )
  {
    std::lock( this->mutex, matrix.mutex );
    LockGuard lock_myself( this->mutex, std::adopt_lock );
    LockGuard lock_rhs( matrix.mutex, std::adopt_lock );
    
    this->elements = matrix.elements;
    this->rows = matrix.rows;
    this->columns = matrix.columns;
  }



  // Constructs a Matrix from the matrix by moving elements
  Matrix( const Matrix< T >&& matrix )
  {
    std::lock( this->mutex, matrix.mutex );
    LockGuard lock_myself( this->mutex, std::adopt_lock );
    LockGuard lock_rhs( matrix.mutex, std::adopt_lock );
    
    this->elements = std::move( matrix.elements );
    this->rows = matrix.rows;
    this->columns = matrix.columns;
  }



  // Retrieves a reference
  T& operator() ( Index row, Index column );
  const T& operator() ( Index row, Index column ) const;
  
  // Copy-based assignment
  Matrix< T >& operator= ( const Matrix< T >& rhs );
  
  // Move-based assignment
  Matrix< T >& operator= ( const Matrix< T >&& rhs );
  
  // Matrix operations
  Matrix< T >& operator+ ( const Matrix< T >& rhs );
  Matrix< T >& operator- ( const Matrix< T >& rhs );
  Matrix< T >& operator* ( const Matrix< T >& rhs );



  bool operator== ( const Matrix< T >& rhs ) const
  {
    if ( &rhs == this ) {
      return true;
    }
    
    std::lock( this->mutex, rhs.mutex );
    LockGuard lock_myself( this->mutex, std::adopt_lock );
    LockGuard lock_rhs( rhs.mutex, std::adopt_lock );
    
    std::valarray< bool > comp = ( this->elements == rhs.elements );
    bool isEqual = ( comp.min() == true );
    
    return isEqual;
  }



  bool operator!= ( const Matrix< T >& rhs ) const
  {
    return !( *this == rhs );
  }
  
  
  
  Matrix< T >& transpose();
  
  // Retrieves dimensions
  Index get_rows() const;
  Index get_columns() const;

private:
  // Setters and getters for access handling
  T& get( Index row, Index column );
  const T& get( Index row, Index column ) const;
  void set( Index row, Index column, const T& value );

  mutable std::mutex mutex;
  std::valarray< T > elements;
  Index rows;
  Index columns;
};



// Non-member functions

// Scalar multiplication
template< typename T >
Matrix< T >& operator* ( const T& value , Matrix< T >& matrix )
{
  // TODO: scalar multiplication
}



#endif // MATRIX_H
