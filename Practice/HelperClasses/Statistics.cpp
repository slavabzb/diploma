#include "Statistics.h"

#include <fstream>
#include <iostream>

#include "HelperClasses/Logger.h"



Time& Statistics::operator() ( std::size_t matrixSize, StatisticsType statisticsType )
{
  return this->statisticsArray[ statisticsType ][ matrixSize ];
}



void Statistics::save( const std::string& fileName )
{
  std::fstream fstream( fileName, std::fstream::out );
  std::ostream* ostream;
  
  if( fstream.is_open() ) {
    ostream = &fstream;
  }
  else {
    ostream = &std::clog;
    *ostream << "\nWarning! Can't open file " << fileName << "; redirect stream to std::clog.\n";
  }
  
  *ostream << "Statistics report.\n\n";
  
  *ostream << "The sizes of the matrices: ";
  for( auto it = this->statisticsArray[ Multiplication ].cbegin(); it != this->statisticsArray[ Multiplication ].cend(); ++it ) {
    *ostream << it->first << ' ';
  }
  
  for( StatisticsType statisticsType = Addition; statisticsType != StatisticsTypeSize;
    statisticsType = static_cast< StatisticsType >( static_cast< std::size_t >(statisticsType) + 1 ) ) {
    
    *ostream << "\nTime statistics for " << this->statisticsTypeNames.at( statisticsType ) << ".";
    
    *ostream << "\nOut-of-class time: ";
    for( auto it = this->statisticsArray[ statisticsType ].cbegin(); it != this->statisticsArray[ statisticsType ].cend(); ++it ) {
      *ostream << it->second.getSingleThreadTime() << ' ';
    }
    
    *ostream << "\nIn-class time: ";
    for( auto it = this->statisticsArray[ statisticsType ].cbegin(); it != this->statisticsArray[ statisticsType ].cend(); ++it ) {
      *ostream << it->second.getMultyThreadTime() << ' ';
    }
  
    *ostream << "\nAcceleration: ";
    for( auto it = this->statisticsArray[ statisticsType ].cbegin(); it != this->statisticsArray[ statisticsType ].cend(); ++it ) {
      *ostream << it->second.getSingleThreadTime() / it->second.getMultyThreadTime() << ' ';
    }
    
    *ostream << "\n\n";
  }
}



