#include "Statistics.h"

#include <fstream>
#include <iostream>



Statistics::Type& operator++ ( Statistics::Type& statistics_type )
{
  statistics_type = static_cast< Statistics::Type >(
    static_cast< int >( statistics_type ) + 1
  );
  
  return statistics_type;
}



Time& Statistics::operator() ( std::size_t matrix_size,
  Statistics::Type statistics_type )
{
  return this->statistics_array[ statistics_type ][ matrix_size ];
}



void Statistics::save( const std::string& file )
{
  std::fstream fstream( file, std::fstream::out );
  
  if( !fstream.is_open() ) {
    std::cerr << "Can't open file " << file << ".\n";
  }
  
  fstream << "Statistics report.\n\n";
  
  fstream << "The sizes of the matrices: ";
  for( auto pair : this->statistics_array[ Statistics::Type::Multiplication ] ) {
    fstream << pair.first << ' ';
  }
  
  for( Statistics::Type statistics_type = Statistics::Type::Addition;
    statistics_type != Statistics::Type::Size; ++statistics_type )
  {
    fstream << "\n\nTime statistics for "
      << this->statistics_type_names_map.at( statistics_type ) << ".";
    
    fstream << "\nSingle thread time: ";
    for( auto pair : this->statistics_array[ statistics_type ] ) {
      fstream << pair.second.get_single_thread_time() << ' ';
    }
    
    fstream << "\nMultiple threads time: ";
    for( auto pair : this->statistics_array[ statistics_type ] ) {
      fstream << pair.second.get_multiple_threads_time() << ' ';
    }
  
    fstream << "\nAcceleration: ";
    for( auto pair : this->statistics_array[ statistics_type ] ) {
      fstream << pair.second.get_single_thread_time() /
        pair.second.get_multiple_threads_time() << ' ';
    }
    
    fstream << "\n";
  }
}



