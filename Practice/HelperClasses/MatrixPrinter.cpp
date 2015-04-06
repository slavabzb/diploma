#include "MatrixPrinter.h"



MatrixPrinter::MatrixPrinter( std::ostream* ostream )
{
  assert( ostream != nullptr );
  
  this->ostream = ostream;
  this->ostream->setf( std::ios::fixed, std:: ios::floatfield );

  this->setPrecision( 6 );
  
  this->rowDelimiter = "\n";
  this->columnDelimiter = " ";
  this->matricesDelimiter = "\n";
}


  
void MatrixPrinter::setPrecision( std::streamsize precision )
{
  this->precision = precision;
  this->ostream->precision( this->precision );
}


  
void MatrixPrinter::setStream( std::ostream& ostream )
{
  this->ostream = &ostream;
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



