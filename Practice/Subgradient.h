#ifndef SUBGRADIENT
#define SUBGRADIENT



template< typename Point >
class Subgradient
{
protected:

  typedef Point point_t;



public:

  virtual ~Subgradient()
  {
  
  }



  virtual point_t operator() ( const point_t& point ) const = 0;
};



#endif // SUBGRADIENT
