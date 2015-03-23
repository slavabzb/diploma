#include "MatrixPrinter.h"



MatrixPrinter::MatrixPrinter( std::ostream* stream )
{
  assert( stream != nullptr );
    
  this->stream = stream;
  this->precision = 6;
  this->rowDelimiter = "\n";
  this->columnDelimiter = " ";
}


  
void MatrixPrinter::setPrecision( std::streamsize precision )
{
  this->precision = precision;
}


  
void MatrixPrinter::setStream( std::ostream& stream )
{
  this->stream = &stream;
}


  
void MatrixPrinter::setRowDelimiter( const std::string& rowDelimiter )
{
  this->rowDelimiter = rowDelimiter;
}


  
void MatrixPrinter::setColumnDelimiter( const std::string& columnDelimiter )
{
  this->columnDelimiter = columnDelimiter;
}



std::streamsize MatrixPrinter::getPrecision() const
{
  return this->precision;
}



std::string MatrixPrinter::getRowDelimiter() const
{
  return this->rowDelimiter;
}



std::string MatrixPrinter::getColumnDelimeter() const
{
  return this->columnDelimiter;
}



