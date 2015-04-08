#ifndef LOGGER
#define LOGGER

#include <iostream>



class Logger
{
public:

  static Logger* getInstance();



  template< typename T >
  Logger* write( const T& message )
  {
    std::clog << message;
    
    return Logger::getInstance();
  }
  
  
  
  Logger* write( double value )
  {
    std::clog.setf( std::ios::fixed, std:: ios::floatfield );
    std::clog.precision( 2 );
    std::clog.width( 6 );

    std::clog << value;
    
    return Logger::getInstance();
  }



private:

  Logger() = default;
  Logger& operator=( const Logger& rhs ) = delete;
  
};



#endif // LOGGER
