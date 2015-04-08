#include "Statistics.h"

#include <fstream>



Time& Statistics::operator() ( std::size_t matrixSize, StatisticsType statisticsType )
{
  return this->statisticsArray[ statisticsType ][ matrixSize ];
}



void Statistics::save( const std::string& fileName )
{
  std::ofstream ofstream( fileName );
  ofstream << "Statistics report.\n\n";
  
  ofstream << "The sizes of the matrices: ";
  for( auto it = this->statisticsArray[ Multiplication ].cbegin(); it != this->statisticsArray[ Multiplication ].cend(); ++it ) {
    ofstream << it->first << ' ';
  }
  
  for( StatisticsType statisticsType = Addition; statisticsType != StatisticsTypeSize;
    statisticsType = static_cast< StatisticsType >( static_cast< std::size_t >(statisticsType) + 1 ) ) {
    
    ofstream << "\nTime statistics for " << this->statisticsTypeNames.at( statisticsType ) << ".";
    
    ofstream << "\nOut-of-class time: ";
    for( auto it = this->statisticsArray[ statisticsType ].cbegin(); it != this->statisticsArray[ statisticsType ].cend(); ++it ) {
      ofstream << it->second.getSingleThreadTime() << ' ';
    }
    
    ofstream << "\nIn-class time: ";
    for( auto it = this->statisticsArray[ statisticsType ].cbegin(); it != this->statisticsArray[ statisticsType ].cend(); ++it ) {
      ofstream << it->second.getMultyThreadTime() << ' ';
    }
  
    ofstream << "\nAcceleration: ";
    for( auto it = this->statisticsArray[ statisticsType ].cbegin(); it != this->statisticsArray[ statisticsType ].cend(); ++it ) {
      ofstream << it->second.getSingleThreadTime() / it->second.getMultyThreadTime() << ' ';
    }
    
    ofstream << "\n\n";
  }
}



