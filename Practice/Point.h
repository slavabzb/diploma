#ifndef POINT_H
#define POINT_H

#include <array>
#include <iostream>



template< typename T, std::size_t N >
class Point
{
  typedef T value_t;
  typedef std::array< value_t, N > values_container_t;
  typedef Point< value_t, N > my_t;
  typedef std::size_t index_t;

  using size_t = typename values_container_t::size_type;



public:

  void print() const
  {
    for( const auto& value : this->values ) {
      std::cout << value << ' ';
    }
    std::cout << '\n';
  }



  template< typename... Values >
  Point( const Values&... values )
    : values{ values... }
  {

  }



  size_t size() const
  {
    return this->values.size();
  }



  value_t& operator[] ( const index_t& index )
  {
    return this->values[ index ];
  }



  const value_t& operator[] ( const index_t& index ) const
  {
    return this->values[ index ];
  }



  my_t& operator= ( const my_t& rhs )
  {
    if( this == &rhs ) {
      return *this;
    }
    
    this->values = rhs.values;
    
    return *this;
  }



  my_t operator+ ( const my_t& rhs ) const
  {
    my_t result;
    
    for( size_t index = 0; index < result.values.size(); ++index ) {
      result.values[ index ] = ( this->values[ index ] + rhs.values[ index ] );
    }
    
    return result;
  }



  my_t operator- ( const my_t& rhs ) const
  {
    my_t result;
    
    for( size_t index = 0; index < result.values.size(); ++index ) {
      result.values[ index ] = ( this->values[ index ] - rhs.values[ index ] );
    }
    
    return result;
  }



  my_t& operator+= ( const my_t& rhs )
  {
    for( size_t index = 0; index < this->values.size(); ++index ) {
      this->values[ index ] += rhs.values[ index ];
    }
    
    return *this;
  }



  my_t& operator-= ( const my_t& rhs )
  {
    for( size_t index = 0; index < this->values.size(); ++index ) {
      this->values[ index ] -= rhs.values[ index ];
    }
    
    return *this;
  }



private:

  values_container_t values;
};



#endif // POINT_H
