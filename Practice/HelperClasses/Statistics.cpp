#include "Statistics.h"

#include <fstream>



void TimeStatisticsPrinter::print( const std::string& message, const TimeStatistics& timeStatistics )
{
  this->stringstream << message << ":\n";
  this->stringstream << "Helper class time:\n";
  for( auto it = timeStatistics.begin(); it != timeStatistics.end(); ++it ) {
    this->stringstream << it->second.singleTime << ' ';
  }
  this->stringstream << "\n\nMatrix class time:\n";
  for( auto it = timeStatistics.begin(); it != timeStatistics.end(); ++it ) {
    this->stringstream << it->second.multyTime << ' ';
  }
  this->stringstream << "\n\n\n";
}



void TimeStatisticsPrinter::save( const std::string& fileName )
{
  std::ofstream ofstream;
  ofstream.open( fileName );
  ofstream << this->stringstream.str();
  ofstream.close();
}



