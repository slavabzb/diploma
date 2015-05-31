#ifndef MATRIX_PRINTER
#define MATRIX_PRINTER

#include <ostream>
#include <string>

#include "Matrix.h"



class MatrixPrinter
{
public:

  MatrixPrinter( std::ostream* ostream );



  template< typename T >
  void print( const Matrix< T >& matrix )
  {
    *this->ostream << this->matrices_delimiter;   
    
    for ( std::size_t row = 0; row < matrix.get_rows(); ++row ) {
      for ( std::size_t column = 0; column < matrix.get_columns(); ++column ) {
        *this->ostream << matrix( row, column ) << this->column_delimiter;
      }
      *this->ostream << this->row_delimiter;
    }
  }
  
  
  
  void set_precision( std::streamsize precision );
  void set_stream( std::ostream& ostream );
  void set_row_delimiter( const std::string& row_delimiter );
  void set_column_delimiter( const std::string& column_delimiter );

  std::streamsize get_precision() const;
  std::string get_row_delimiter() const;
  std::string get_column_delimeter() const;

private:

  std::ostream* ostream;
  std::streamsize precision;
  std::string row_delimiter;
  std::string column_delimiter;
  std::string matrices_delimiter;
};



#endif // MATRIX_PRINTER
