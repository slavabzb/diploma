#ifndef STATISTICS
#define STATISTICS

#include <array>
#include <map>

#include "Time.h"



class Statistics
{
public:

  enum StatisticsType
  {
    Addition,
    Multiplication,
    StatisticsTypeSize
  };

  //StatisticsType& operator++ ( StatisticsType& statistics_type );

  
  Time& operator() ( std::size_t matrixSize, StatisticsType statisticsType );
  void save( const std::string& fileName );



private:

  const std::map< StatisticsType, std::string > statisticsTypeNames = {
    { Addition, "Addition" },
    { Multiplication, "Multiplication" }
  };
  
  typedef std::map< std::size_t, Time > TimeStatistics;
  std::array< TimeStatistics, StatisticsTypeSize > statisticsArray;
};
  
  

#endif // STATISTICS
