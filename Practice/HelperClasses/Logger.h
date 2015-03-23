#ifndef LOGGER
#define LOGGER

#include <fstream>



class Logger
{
public:

  ~Logger();
  
  static Logger* getInstance();
  
  Logger* whiteSpace();
  
  
  template< typename T >
  Logger* write( const T& message )
  {
    this->ofstream << message;
    
    return Logger::getInstance();
  }
  
  

private:

  Logger();
  Logger& operator=( const Logger& rhs ) = delete;
  
  
  std::ofstream ofstream;
  const std::string space;
};



#endif // LOGGER
