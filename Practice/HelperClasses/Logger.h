#ifndef LOGGER
#define LOGGER

#include <fstream>



class Logger
{
public:

  ~Logger();

  static Logger* getInstance();
  
  std::streamsize getPrecision() const;


  template< typename T >
  Logger* write( const T& message, std::streamsize fieldWide = Logger::getInstance()->getPrecision() + 6 )
  {
    this->ofstream.width( fieldWide );
        
    this->ofstream << message;
    
    return Logger::getInstance();
  }


private:

  Logger();
  Logger& operator=( const Logger& rhs ) = delete;
  
  
  std::ofstream ofstream;
  std::streamsize precision;
};



#endif // LOGGER
