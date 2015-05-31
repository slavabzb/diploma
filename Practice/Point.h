#ifndef POINT
#define POINT

#include <initializer_list>

#include "Matrix.h"
#include "Specializations.h"



/**
 * Represents a n-dimensional point (vector).
 */
template< typename T, std::size_t Dimension >
class Point : public Matrix< T >
{
  typedef T value_t;                        /**< A type of point elements. */
  typedef std::size_t index_t;              /**< A type of point index.    */
  typedef Matrix< value_t > base_t;         /**< A type of base class.     */
  typedef Point< value_t, Dimension > my_t; /**< A type of point.          */



public:

  /**
   * A default constructor.
   * Constructs a point with Dimension elements filled by 0.
   */
  Point()
    : base_t( Dimension, 1 )
  {

  }



  /**
   * A copy constructor.
   */
  Point( const base_t& rhs )
    : base_t( rhs )
  {
    assert( rhs.get_rows() == Dimension );
    assert( rhs.get_columns() == 1 );
  }



  /**
   * A constructor.
   * Constructs a point from brace-init-list.
   */
  Point( std::initializer_list< T > list )
    : base_t( Dimension, 1 )
  {
    index_t index = 0;
    for( auto it = list.begin(); it != list.end(); ++it ) {
      ( *this )[ index ] = *it;
      ++index;
    }
  }



  /**
   * A substraction operator.
   */
  my_t& operator-= ( const my_t& rhs )
  {
    for( index_t index = 0; index < this->size(); ++index ) {
      ( *this )[ index ] -= rhs[ index ];
    }
    
    return *this;
  }



  /**
   * An additional operator.
   */
  my_t& operator+= ( const my_t& rhs )
  {
    for( index_t index = 0; index < this->size(); ++index ) {
      ( *this )[ index ] += rhs[ index ];
    }
    
    return *this;
  }



  /**
   * A multiplying operator.
   */
  my_t& operator*= ( const value_t& rhs )
  {
    *this = ( *this ) * rhs;
    
    return *this;
  }



  /**
   * A comparison operator.
   */
  bool operator== ( const base_t& rhs ) const
  {
    return ( *dynamic_cast< const base_t* >( this ) ) == rhs;
  }



  /**
   * A comparison operator.
   */
  bool operator== ( const value_t& rhs ) const
  {
    bool is_all_equal = true;
    for( index_t index = 0; index < this->size(); ++index ) {
      if( ( *this )[ index ] != rhs ) {
        is_all_equal = false;
        break;
      }
    }
    
    return is_all_equal;
  }



  /**
   * A comparison operator.
   */
  bool operator!= ( const my_t& rhs ) const
  {
    return !( ( *this ) == rhs );
  }



  /**
   * A comparison operator.
   */
  bool operator!= ( const value_t& rhs ) const
  {
    return !( ( *this ) == rhs );
  }



  /**
   * Size of the point.
   * Retrieve a number of the elements of the point.
   */
  std::size_t size() const
  {
    return base_t::get_rows();
  }



  /**
   * An index-based accessor.
   */
  value_t& operator[] ( const index_t& index )
  {
    return ( *this )( index, 0 );
  }



  /**
   * A const index-based accessor.
   */
  const value_t& operator[] ( const index_t& index ) const
  {
    return ( *this )( index, 0 );
  }



  /**
   * Euclidian norm.
   * Calculates an euclidian norm of the vector.
   */
  value_t norm() const
  {
    value_t sum_square( 0 );
    for( index_t index = 0; index < this->size(); ++index ) {
      value_t value = ( *this )[ index ];
      sum_square += std::pow( value, 2 );
    }
    
    return std::sqrt( sum_square );
  }



private:

  /**
   * A private accessor.
   * Retrieve the reference by index.
   */
  value_t& operator() ( const index_t& row, const index_t& column )
  {
    return base_t::operator() ( row, column );
  }



  /**
   * A const private accessor.
   * Retrieve the const reference by index.
   */
  const value_t& operator() ( const index_t& row, const index_t& column ) const
  {
    return base_t::operator() ( row, column );
  }



  /**
   * Restrict access to the following entities from base class.
   */
  std::size_t get_rows() const;
  std::size_t get_columns() const;
  class Type;
};



#endif // POINT
