#include "MatrixPrinter.h"



MatrixPrinter::MatrixPrinter( std::ostream* ostream )
{
  assert( ostream != nullptr );
  
  this->ostream = ostream;
  this->ostream->setf( std::ios::fixed, std:: ios::floatfield );

  this->set_precision( 6 );
  
  this->row_delimiter = "\n";
  this->column_delimiter = " ";
  this->matrices_delimiter = "\n";
}


  
void MatrixPrinter::set_precision( std::streamsize precision )
{
  this->precision = precision;
  this->ostream->precision( this->precision );
}


  
void MatrixPrinter::set_stream( std::ostream& ostream )
{
  this->ostream = &ostream;
}


  
void MatrixPrinter::set_row_delimiter( const std::string& row_delimiter )
{
  this->row_delimiter = row_delimiter;
}


  
void MatrixPrinter::set_column_delimiter( const std::string& column_delimiter )
{
  this->column_delimiter = column_delimiter;
}



std::streamsize MatrixPrinter::get_precision() const
{
  return this->precision;
}



std::string MatrixPrinter::get_row_delimiter() const
{
  return this->row_delimiter;
}



std::string MatrixPrinter::get_column_delimeter() const
{
  return this->column_delimiter;
}



