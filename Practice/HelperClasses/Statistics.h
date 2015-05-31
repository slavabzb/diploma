#ifndef STATISTICS
#define STATISTICS

#include <array>
#include <map>

#include "Time.h"



class Statistics
{
public:

  enum Type : std::int8_t
  {
    Addition,
    Multiplication,
    Size
  };
  
  Time& operator() ( std::size_t matrix_size, Statistics::Type statistics_type );
  void save( const std::string& file );



private:

  const std::map< Statistics::Type, std::string > statistics_type_names_map = {
    { Statistics::Type::Addition, "Addition" },
    { Statistics::Type::Multiplication, "Multiplication" }
  };
  
  typedef std::map< std::size_t, Time > time_statistics_t;
  std::array< time_statistics_t, Statistics::Type::Size > statistics_array;
};
  
  

#endif // STATISTICS
