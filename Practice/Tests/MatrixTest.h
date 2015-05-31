#ifndef MATRIX_TEST
#define MATRIX_TEST

#include <gmpxx.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "Matrix.h"

#include "HelperClasses/MatrixRandomFiller.h"
#include "HelperClasses/Statistics.h"
#include "HelperClasses/TimeMeasurer.h"



class MatrixTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( MatrixTest );
      CPPUNIT_TEST( addition );
      CPPUNIT_TEST( multiplication );
      CPPUNIT_TEST( transposition );
      CPPUNIT_TEST( acceleration );
      CPPUNIT_TEST( multiple_threads_time );
      CPPUNIT_TEST( threads_number_time );
      CPPUNIT_TEST( matrix_types );
    CPPUNIT_TEST_SUITE_END();
  
public:
  
  void crash_double_type();
  void addition();
  void multiplication();
  void transposition();
  void acceleration();
  void multiple_threads_time();
  void threads_number_time();
  void matrix_types();
  
private:

  template< typename Function >
  double calculate_average_time( Function&& function ) {
    TimeMeasurer time_measurer;
    std::valarray< double > durations( this->inner_loop_iterations_num );
    for( std::size_t duration = 0; duration < durations.size(); ++duration ) {
      time_measurer.start();
      function();
      time_measurer.end();
      durations[ duration ] = time_measurer.get_duration_in_seconds();
    }
    
    return durations.sum() / durations.size();
  }



  typedef mpf_class value_t;
  typedef Matrix< value_t > matrix_t;
  
  std::size_t matrix_size = 50;
  std::size_t initial_size = 10;
  std::size_t size_step = 10;
  std::size_t iterations_num = 0;
  std::size_t inner_loop_iterations_num = 1;

  Statistics statistics;
  MatrixRandomFiller matrix_random_filler;
};



#endif // MATRIX_TEST
