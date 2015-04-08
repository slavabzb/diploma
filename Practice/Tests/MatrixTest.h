#ifndef MATRIX_TEST
#define MATRIX_TEST

#include <memory>
#include <gmpxx.h>

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

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
    CPPUNIT_TEST( testTime );
  CPPUNIT_TEST_SUITE_END();
  
public:
  
  void testAddition();
  void testMultiplication();
  void testTransposition();
  void testTime();
  
private:
  
  typedef mpz_class element_t;
  typedef Matrix< element_t > matrix_t;
  
  
  
  MatrixRandomFiller matrixRandomFiller;
  MatrixSummarizer matrixSummarizer;
  MatrixMultiplier matrixMultiplier;
  MatrixTransposer matrixTransposer;
  
  TimeMeasurer timeMeasurer;
  
  std::size_t matrixSize = 50;
};



#endif // MATRIX_TEST
