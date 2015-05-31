#include "TimeMeasurer.h"



void TimeMeasurer::start()
{
  this->start_time_point = std::chrono::high_resolution_clock::now();
}



void TimeMeasurer::end()
{
  this->end_time_point = std::chrono::high_resolution_clock::now();
  this->interval = std::chrono::duration_cast< std::chrono::duration< double > >(
    this->end_time_point - this->start_time_point
  );
}



double TimeMeasurer::get_duration_in_seconds() const
{
  return this->interval.count();
}



