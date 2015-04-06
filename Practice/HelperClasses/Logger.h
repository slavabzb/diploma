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



private:

  Logger() = default;
  Logger& operator=( const Logger& rhs ) = delete;
  
};



#endif // LOGGER
