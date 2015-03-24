#include "Logger.h"



Logger::Logger()
  : ofstream( "log" )
{
  this->precision = 10;
  
  this->ofstream.precision( this->precision );
  this->ofstream.setf( std::ios::fixed, std::ios::floatfield );
  this->ofstream.setf( std::ios_base::left );
  
  this->ofstream << "Matrix class test statistics.\n\n";
  this->ofstream << "The precision is " << this->ofstream.precision() << " decimal places.\n\n";
    
  const std::string header[] = {
    "Iter",
    "Size",
    "Single",
    "Multy",
    "Acceleration"
  };
  
  this->ofstream << header[ 0 ] << " - is the number of iteration;\n";
  this->ofstream << header[ 1 ] << " - is the sizes of the test square matrices (N x N);\n";
  this->ofstream << header[ 2 ] << " - [ T1 ] is the time span in seconds of performing current operation in single thread;\n";
  this->ofstream << header[ 3 ] << " - [ T2 ] is the time span in seconds of performing current operation in multiple threads;\n";
  this->ofstream << header[ 4 ] << " - is the ratio of T2 to T1.\n\n";
  
  this->ofstream << "\n-------------------------------------------------------\n";
  
  this->ofstream.width( 5 );
  this->ofstream << header[ 0 ];
  
  this->ofstream.width( 6 );
  this->ofstream << header[ 1 ];
  
  this->ofstream.width( this->precision + 6 );
  this->ofstream << header[ 2 ];
  
  this->ofstream.width( this->precision + 6 );
  this->ofstream << header[ 3 ];
  
  this->ofstream.width( this->precision + 6 );
  this->ofstream << header[ 4 ];
  
  this->ofstream << "\n-------------------------------------------------------\n";
}



Logger::~Logger()
{
  this->ofstream << "\n-------------------------------------------------------\n\n";
  this->ofstream.close();
}



Logger* Logger::getInstance()
{
  static Logger instance;
  
  return &instance;
}



std::streamsize Logger::getPrecision() const
{
  return this->precision;
}



