#include "Statistics.h"

#include <fstream>



void TimeStatisticsPrinter::print( const std::string& message, const TimeStatistics& timeStatistics )
{
  this->stringstream << "Time statistics for \"" << message << "\".\n";
  this->stringstream << "The sizes of the matrices: ";
  for( auto it = timeStatistics.cbegin(); it != timeStatistics.cend(); ++it ) {
    this->stringstream << it->first << ' ';
  }
  this->stringstream << "\nHelper class time: ";
  for( auto it = timeStatistics.cbegin(); it != timeStatistics.cend(); ++it ) {
    this->stringstream << it->second.singleTime << ' ';
  }
  this->stringstream << "\nMatrix class time: ";
  for( auto it = timeStatistics.cbegin(); it != timeStatistics.cend(); ++it ) {
    this->stringstream << it->second.multyTime << ' ';
  }
  this->stringstream << "\nAcceleration: ";
  for( auto it = timeStatistics.cbegin(); it != timeStatistics.cend(); ++it ) {
    this->stringstream << it->second.singleTime / it->second.multyTime << ' ';
  }
  this->stringstream << "\n\n";
}



void TimeStatisticsPrinter::save( const std::string& fileName )
{
  std::ofstream ofstream;
  ofstream.open( fileName );
  ofstream << this->stringstream.str();
  ofstream.close();
}



