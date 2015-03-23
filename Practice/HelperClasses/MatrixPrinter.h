#ifndef MATRIX_PRINTER
#define MATRIX_PRINTER

#include <ostream>
#include <string>

#include "MatrixOperationPerformer.h"



class MatrixPrinter : public MatrixOperationPerformer
{
public:

  MatrixPrinter( std::ostream* ostream );



  template< typename T >
  void print( const Matrix< T >& matrix )
  {
    *this->ostream << this->matricesDelimiter;   
    
    for ( std::size_t iRow = 0; iRow < matrix.get_rows(); ++iRow ) {
      for ( std::size_t iColumn = 0; iColumn < matrix.get_columns(); ++iColumn ) {
        *this->ostream << matrix( iRow, iColumn ) << this->columnDelimiter;
      }
      *this->ostream << this->rowDelimiter;
    }
  }
  
  
  
  void setPrecision( std::streamsize precision );
  void setStream( std::ostream& ostream );
  void setRowDelimiter( const std::string& rowDelimiter );
  void setColumnDelimiter( const std::string& columnDelimiter );

  std::streamsize getPrecision() const;
  std::string getRowDelimiter() const;
  std::string getColumnDelimeter() const;

private:

  std::ostream* ostream;
  std::streamsize precision;
  std::string rowDelimiter;
  std::string columnDelimiter;
  std::string matricesDelimiter;
};



#endif // MATRIX_PRINTER
