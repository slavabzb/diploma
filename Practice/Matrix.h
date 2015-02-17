#ifndef MATRIX_H
#define MATRIX_H

#include <valarray>

// Represents matrix
template< typename T >
class Matrix
{
public:
  typedef std::size_t Index;
  
  // Constructs an empty Matrix
  Matrix();
  
  // Constructs a rows-by-columns Matrix with each element initialized to the initializer value
  Matrix( Index rows, Index columns, const T& initializer = T( 0 ) );
  
  // Constructs a Matrix from the matrix by copying elements
  Matrix( const Matrix< T >& matrix );
  
  // Constructs a Matrix from the matrix by moving elements
  Matrix( const Matrix< T >&& matrix );
  
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
  
  bool operator== ( const Matrix< T >& rhs ) const;
  
  Matrix< T >& transpose();
  
  // Retrieves dimensions
  Index get_rows() const;
  Index get_columns() const;

private:
  // Setters and getters for access handling
  T& get( Index row, Index column );
  const T& get( Index row, Index column ) const;
  void set( Index row, Index column, const T& value );

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



// Member functions

template< typename T >
Matrix< T >::Matrix()
{
  // TODO: default constructor
}



template< typename T >
Matrix< T >::Matrix( typename Matrix< T >::Index rows, typename Matrix< T >::Index columns, const T& initializer )
{
  // TODO: initialize all class members
}



template< typename T >
Matrix< T >::Matrix( const Matrix< T >& matrix )
{
  // TODO: copy constructor
}



template< typename T >
Matrix< T >::Matrix( const Matrix< T >&& matrix )
{
  // TODO: move constructor
}



template< typename T >
T& Matrix< T >::operator() ( typename Matrix< T >::Index row, typename Matrix< T >::Index column )
{
  // TODO: get reference
}



template< typename T >
const T& Matrix< T >::operator() ( typename Matrix< T >::Index row, typename Matrix< T >::Index column ) const
{
  // TODO: get const reference
}



template< typename T >
Matrix< T >& Matrix< T >::operator= ( const Matrix< T >& rhs )
{
  // TODO: copy-based assignment
}



template< typename T >
Matrix< T >& Matrix< T >::operator= ( const Matrix< T >&& rhs )
{
  // TODO: move-based assignment
}



template< typename T >
typename Matrix< T >::Index Matrix< T >::get_rows() const
{
  // TODO: return rows
}



template< typename T >
typename Matrix< T >::Index Matrix< T >::get_columns() const
{
  // TODO: return columns
}



template< typename T >
T& Matrix< T >::get( typename Matrix< T >::Index row, typename Matrix< T >::Index column )
{
  // TODO: getter
}



template< typename T >
const T& Matrix< T >::get( typename Matrix< T >::Index row, typename Matrix< T >::Index column ) const
{
  // TODO: const getter
}



template< typename T >
void Matrix< T >::set( typename Matrix< T >::Index row, typename Matrix< T >::Index column, const T& value )
{
  // TODO: setter
}



template< typename T >
Matrix< T >& Matrix< T >::operator+ ( const Matrix< T >& rhs )
{
  // TODO: addition
}



template< typename T >
Matrix< T >& Matrix< T >::operator- ( const Matrix< T >& rhs )
{
  // TODO: substraction
}



template< typename T >
Matrix< T >& Matrix< T >::operator* ( const Matrix< T >& rhs )
{
  // TODO: multiplication
}



template< typename T >
bool Matrix< T >::operator== ( const Matrix< T >& rhs ) const
{
  // TODO: component-wise comparison
}



template< typename T >
Matrix< T >& Matrix< T >::transpose()
{
  // TODO: transposition
}


  
#endif // MATRIX_H
