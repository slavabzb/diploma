#ifndef MATRIX_H
#define MATRIX_H

#include <valarray>

// Represents matrix
template< typename T >
class Matrix
{
public:
  // Constructs an empty Matrix
  Matrix();
  
  // Constructs a rows-by-columns Matrix with each element initialized to the initializer value
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
  
  Matrix< T > transpose() const;
  
  Matrix< T > submatrix( std::size_t row_to_remove, std::size_t column_to_remove ) const;
  
  // Row operations
  void row_swap( std::size_t row1, std::size_t row2 );
  void row_multiply( std::size_t row, const T& multiplier );
  void row_add( std::size_t target_row, std::size_t sourse_row, const T& source_row_multiplier = T( 1 ) );
  
  // Column operations
  void column_swap( std::size_t column1, std::size_t column2 );
  void column_multiply( std::size_t column, const T& multiplier );
  void column_add( std::size_t target_column, std::size_t sourse_column, const T& source_column_multiplier = T( 1 ) );
  
  // Retrieves dimensions
  std::size_t get_rows() const;
  std::size_t get_columns() const;
  
  // Retrieves type of the Matrix
  bool is_empty() const;
  bool is_square() const;

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
template< typename T >
Matrix< T >& operator* ( const T& value , Matrix< T >& matrix )
{
  // TODO: scalar multiplication
}



// Implementations

template< typename T >
Matrix< T >::Matrix()
{
  // TODO: default constructor
}



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
bool Matrix< T >::is_empty() const
{
  // TODO: check if the Matrix is empty
}



template< typename T >
bool Matrix< T >::is_square() const
{
  // TODO: check if the Matrix is square
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
Matrix< T > Matrix< T >::transpose() const
{
  // TODO: transposition of const Matrix
}



template< typename T >
Matrix< T > submatrix( std::size_t row_to_remove, std::size_t column_to_remove ) const
{
  // TODO: return submatrix
}



template< typename T >
void Matrix< T >::row_swap( std::size_t row1, std::size_t row2 )
{
  // TODO: swap rows
}



template< typename T >
void Matrix< T >::row_multiply( std::size_t row, const T& multiplier )
{
  // TODO: multiply row by value
}



template< typename T >
void Matrix< T >::row_add( std::size_t target_row, std::size_t sourse_row, const T& source_row_multiplier )
{
  // TODO: replace row by linear combination
}



template< typename T >
void Matrix< T >::column_swap( std::size_t column1, std::size_t column2 )
{
  // TODO: swap columns
}



template< typename T >
void Matrix< T >::column_multiply( std::size_t column, const T& multiplier )
{
  // TODO: multiply column by value
}



template< typename T >
void Matrix< T >::column_add( std::size_t target_column, std::size_t sourse_column, const T& source_column_multiplier )
{
  // TODO: replace column by linear combination
}


  
#endif // MATRIX_H
