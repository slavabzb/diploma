#ifndef MATRIX_PRINTER
#define MATRIX_PRINTER

#include <ostream>
#include <string>

#include "MatrixOperationPerformer.h"



class MatrixPrinter : public MatrixOperationPerformer
{
public:

  MatrixPrinter( std::ostream* stream );



  template< typename T >
  void print( const Matrix< T >& matrix )
  {
    this->stream->precision( this->precision );
    for ( std::size_t iRow = 0; iRow < matrix.get_rows(); ++iRow ) {
      for ( std::size_t iColumn = 0; iColumn < matrix.get_columns(); ++iColumn ) {
        *this->stream << std::fixed << matrix( iRow, iColumn ) << this->columnDelimiter;
      }
      *this->stream << this->rowDelimiter;
    }
  }
  
  
  
  void setPrecision( std::streamsize precision );
  void setStream( std::ostream& stream );
  void setRowDelimiter( const std::string& rowDelimiter );
  void setColumnDelimiter( const std::string& columnDelimiter );

  std::streamsize getPrecision() const;
  std::string getRowDelimiter() const;
  std::string getColumnDelimeter() const;

private:

  std::ostream* stream;
  std::streamsize precision;
  std::string rowDelimiter;
  std::string columnDelimiter;
};



#endif // MATRIX_PRINTER
