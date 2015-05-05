#ifndef POINT_H
#define POINT_H

#include <initializer_list>
#include <iostream>

#include "Matrix.h"
#include "Specializations.h"



template< typename T, std::size_t Dimension >
class Point : public Matrix< T >
{
  typedef T value_t;
  typedef std::size_t index_t;
  typedef Matrix< value_t > base_t;
  typedef Point< value_t, Dimension > my_t;



public:

  void print() const
  {
    std::cout << "( ";
    for( index_t index = 0; index < this->size(); ++index ) {
      std::cout << ( *this )[ index ] << ' ';
    }
    std::cout << ")\n";
  }



  Point()
    : base_t( Dimension, 1 )
  {

  }



  Point( const base_t& rhs )
    : base_t( rhs )
  {
    assert( rhs.get_rows() == Dimension );
    assert( rhs.get_columns() == 1 );
  }



  Point( std::initializer_list< T > list )
    : base_t( Dimension, 1 )
  {
    index_t index = 0;
    for( auto it = list.begin(); it != list.end(); ++it ) {
      ( *this )[ index ] = *it;
      ++index;
    }
  }



  my_t& operator-= ( const my_t& rhs )
  {
    for( index_t index = 0; index < this->size(); ++index ) {
      ( *this )[ index ] -= rhs[ index ];
    }
    
    return *this;
  }



  my_t& operator+= ( const my_t& rhs )
  {
    for( index_t index = 0; index < this->size(); ++index ) {
      ( *this )[ index ] += rhs[ index ];
    }
    
    return *this;
  }



  bool operator== ( const base_t& rhs ) const
  {
    return ( *dynamic_cast< const base_t* >( this ) ) == rhs;
  }


  bool operator== ( const value_t& rhs ) const
  {
    bool isAllEqual = true;
    for( index_t index = 0; index < this->size(); ++index ) {
      if( ( *this )[ index ] != rhs ) {
        isAllEqual = false;
        break;
      }
    }
    
    return isAllEqual;
  }



  bool operator!= ( const my_t& rhs ) const
  {
    return !( ( *this ) == rhs );
  }



  bool operator!= ( const value_t& rhs ) const
  {
    return !( ( *this ) == rhs );
  }



  std::size_t size() const
  {
    return this->get_rows();
  }



  value_t& operator[] ( const index_t& index )
  {
    return ( *this )( index, 0 );
  }



  const value_t& operator[] ( const index_t& index ) const
  {
    return ( *this )( index, 0 );
  }



  value_t norm() const
  {
    value_t sumSquare( 0 );
    for( index_t index = 0; index < this->size(); ++index ) {
      value_t value = ( *this )[ index ];
      sumSquare += std::pow( value, 2 );
    }
    
    return std::sqrt( sumSquare );
  }



private:

  value_t& operator() ( const index_t& row, const index_t& column )
  {
    return base_t::operator() ( row, column );
  }



  const value_t& operator() ( const index_t& row, const index_t& column ) const
  {
    return base_t::operator() ( row, column );
  }



  std::size_t get_rows() const
  {
    return base_t::get_rows();
  }



  my_t& transpose();
  std::size_t get_columns() const;

  class Type;
};



#endif // POINT_H
