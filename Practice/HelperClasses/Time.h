#ifndef TIME
#define TIME



class Time
{
public:

  void set_single_thread_time( double time )
  {
    this->single_thread_time = time;
  }



  void set_multiple_threads_time( double time )
  {
    this->multiple_threads_time = time;
  }



  double get_single_thread_time() const 
  {
    return this->single_thread_time;
  }



  double get_multiple_threads_time() const
  {
    return this->multiple_threads_time;
  }



private:

  double single_thread_time;
  double multiple_threads_time;
};



#endif // TIME
