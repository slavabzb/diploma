#include "TimeMeasurer.h"



void TimeMeasurer::start()
{
  this->startTimePoint = std::chrono::high_resolution_clock::now();
}



void TimeMeasurer::end()
{
  this->endTimePoint = std::chrono::high_resolution_clock::now();
  this->interval = std::chrono::duration_cast< std::chrono::duration< double > >( this->endTimePoint - this->startTimePoint );
}



double TimeMeasurer::getDurationInSeconds() const
{
  return this->interval.count();
}



