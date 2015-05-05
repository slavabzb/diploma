#ifndef POINT_H
#define POINT_H

#include <initializer_list>
#include <iostream>

#include "Matrix.h"



template< typename T, std::size_t Dimension >
class Point : public Matrix< T >
{
  typedef Matrix< T > base_t;
  typedef typename base_t::value_t value_t;
  typedef typename base_t::index_t index_t;
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



  Point( std::initializer_list< T > list )
    : base_t( Dimension, 1 )
  {
    index_t index = 0;
    for( auto it = list.begin(); it != list.end(); ++it ) {
      ( *this )[ index ] = *it;
      ++index;
    }
  }



  Point( value_t initialValue = value_t( 0 ) )
    : base_t( Dimension, 1, initialValue )
  {

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



  index_t size() const
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



private:

//  value_t& operator() ( const index_t& row, const index_t& column );
//  const value_t& operator() ( const index_t& row, const index_t& column ) const;
//  base_t& transpose();
//  index_t get_rows() const;
//  index_t get_columns() const;
};



#endif // POINT_H
