#ifndef MATRIX_TEST
#define MATRIX_TEST

#include <memory>
#include <gmpxx.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>

#include "Matrix.h"

#include "HelperClasses/MatrixMultiplier.h"
#include "HelperClasses/MatrixRandomFiller.h"
#include "HelperClasses/MatrixSummarizer.h"
#include "HelperClasses/MatrixTransposer.h"
#include "HelperClasses/Statistics.h"
#include "HelperClasses/TimeMeasurer.h"



class MatrixTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( MatrixTest );
    CPPUNIT_TEST( testAddition );
    CPPUNIT_TEST( testMultiplication );
    CPPUNIT_TEST( testTransposition );
    CPPUNIT_TEST( testAcceleration );
    CPPUNIT_TEST( testMultithreadingTime );
    CPPUNIT_TEST( testThreadsNumberTime );
  CPPUNIT_TEST_SUITE_END();
  
public:
  
  void testCrashDoubleType();
  void testAddition();
  void testMultiplication();
  void testTransposition();
  void testAcceleration();
  void testMultithreadingTime();
  void testThreadsNumberTime();
  
private:

  template< typename Function >
  double calculateAverageTime( Function&& function ) {
    TimeMeasurer timeMeasurer;
    std::valarray< double > durations( this->nInnerLoopIterations );
    for( std::size_t iDuration = 0; iDuration < durations.size(); ++iDuration ) {
      timeMeasurer.start();
      function();
      timeMeasurer.end();
      durations[ iDuration ] = timeMeasurer.getDurationInSeconds();
    }
    
    return durations.sum() / durations.size();
  }



  typedef mpz_class element_t;
  typedef Matrix< element_t > matrix_t;
  
  std::size_t matrixSize = 50;
  std::size_t initialSize = 10;
  std::size_t sizeStep = 10;
  std::size_t nIterations = 4;
  std::size_t nInnerLoopIterations = 1;

  Statistics statistics;
  
  MatrixRandomFiller matrixRandomFiller;
  MatrixSummarizer matrixSummarizer;
  MatrixMultiplier matrixMultiplier;
  MatrixTransposer matrixTransposer;
};



#endif // MATRIX_TEST
