#ifndef MATRIX_H
#define MATRIX_H

#include <valarray>

// Represents matrix

template< typename T >
class Matrix
{
public:
  // Constructs a rows-by-columns Matrix with each element initialized to the provided value
  Matrix( std::size_t rows, std::size_t columns, const T& initializer = T( 0 ) );
  
  // Constructs a Matrix from the matrix by copying elements
  Matrix( const Matrix< T >& matrix );
  
  // Constructs a Matrix from the matrix by moving elements
  Matrix( const Matrix< T >&& matrix );
  
  // Retrieves a reference
  T& operator[] ( std::size_t row, std::size_t column );
  const T& operator[] ( std::size_t row, std::size_t column ) const;
  
  // Copy-based assignment
  Matrix< T >& operator= ( const Matrix< T >& rhs );
  
  // Move-based assignment
  Matrix< T >& operator= ( const Matrix< T >&& rhs );
  
  // Matrix operations
  Matrix< T >& operator+ ( const Matrix< T >& rhs );
  Matrix< T >& operator- ( const Matrix< T >& rhs );
  Matrix< T >& operator* ( const Matrix< T >& rhs );
  
  Matrix< T >& transpose();
  
  // Retrieves dimensions
  std::size_t get_rows() const;
  std::size_t get_columns() const;

private:
  // Setters and getters for access handling
  T& get( std::size_t row, std::size_t column );
  const T& get( std::size_t row, std::size_t column ) const;
  void set( std::size_t row, std::size_t column, const T& value );

  std::valarray< T > elements;
  std::size_t rows;
  std::size_t columns;
};



// Non-member functions

// Scalar multiplication
template< typename T, typename D >
Matrix< T >& operator* ( const D& value , Matrix< T >& matrix )
{
  // TODO: scalar multiplication
}



// Implementations

template< typename T >
Matrix< T >::Matrix( std::size_t rows, std::size_t columns, const T& initializer )
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
T& Matrix< T >::operator[] ( std::size_t row, std::size_t column )
{
  // TODO: get reference
}



template< typename T >
const T& Matrix< T >::operator[] ( std::size_t row, std::size_t column ) const
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
std::size_t Matrix< T >::get_rows() const
{
  // TODO: return rows
}



template< typename T >
std::size_t Matrix< T >::get_columns() const
{
  // TODO: return columns
}



template< typename T >
T& Matrix< T >::get( std::size_t row, std::size_t column )
{
  // TODO: getter
}



template< typename T >
const T& Matrix< T >::get( std::size_t row, std::size_t column ) const
{
  // TODO: const getter
}



template< typename T >
void Matrix< T >::set( std::size_t row, std::size_t column, const T& value )
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
Matrix< T >& Matrix< T >::transpose()
{
  // TODO: transposition
}

#endif // MATRIX_H
