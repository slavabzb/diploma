#ifndef TIME
#define TIME



class Time
{
public:

  void setSingleThreadTime( double time )
  {
    this->singleThreadTime = time;
  }



  void setMultyThreadTime( double time )
  {
    this->multyThreadTime = time;
  }



  double getSingleThreadTime() const 
  {
    return this->singleThreadTime;
  }



  double getMultyThreadTime() const
  {
    return this->multyThreadTime;
  }



private:

  double singleThreadTime;
  double multyThreadTime;
};



#endif // TIME
