#ifndef STATISTICS
#define STATISTICS

#include <sstream>
#include <map>



struct TimePair
{
  double singleTime;
  double multyTime;
};



typedef std::map< std::size_t, TimePair > TimeStatistics;



class TimeStatisticsPrinter
{
public:

  void print( const std::string& message, const TimeStatistics& timeStatistics );
  void save( const std::string& fileName );

private:

  std::stringstream stringstream;
};



#endif // STATISTICS
