#include "Logger.h"



Logger::Logger()
  : ofstream( "log" )
  , space( "   " )
{
  this->ofstream.precision( 10 );
  this->ofstream.setf( std::ios::fixed, std:: ios::floatfield );
  
  this->ofstream << "Matrix class test statistics.\n\n"
    << "N" << this->space
    << "Size   " << this->space
    << "Single (sec)" << this->space
    << "Multy (sec) " << this->space
    << "Acceleration\n"
    << "--------------------------------------------------------\n";
}



Logger::~Logger()
{
  this->ofstream << "\n\nThe precision is "
    << this->ofstream.precision()
    << " decimal places.\n";
  this->ofstream.close();
}



Logger* Logger::whiteSpace()
{
  this->ofstream << this->space;
  
  return Logger::getInstance();
}



Logger* Logger::getInstance()
{
  static Logger instance;
  
  return &instance;
}



