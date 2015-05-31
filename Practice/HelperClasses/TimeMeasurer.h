#ifndef TIME_MEASURER
#define TIME_MEASURER

#include <chrono>



class TimeMeasurer
{
public:

  void start();
  void end();
  
  double get_duration_in_seconds() const;

private:

  typedef std::chrono::high_resolution_clock::time_point time_point_t;
  typedef std::chrono::duration< double > interval_t;
  
  time_point_t start_time_point;
  time_point_t end_time_point;
  interval_t interval;
};



#endif // TIME_MEASURER
