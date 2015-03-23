#ifndef TIME_MEASURER
#define TIME_MEASURER

#include <chrono>



class TimeMeasurer
{
public:

  void start();
  void end();
  
  double getDurationInSeconds() const;

private:

  typedef std::chrono::high_resolution_clock::time_point TimePoint;
  typedef std::chrono::duration< double > IntervalDuration;
  
  TimePoint startTimePoint;
  TimePoint endTimePoint;
  IntervalDuration interval;
};



#endif // TIME_MEASURER
