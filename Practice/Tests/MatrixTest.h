#ifndef MATRIX_TEST
#define MATRIX_TEST

#include <memory>
#include <gmpxx.h>

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Matrix.h"

#include "HelperClasses/MatrixRandomFiller.h"
#include "HelperClasses/MatrixSummarizer.h"
#include "HelperClasses/MatrixMultiplier.h"
#include "HelperClasses/MatrixTransposer.h"
#include "HelperClasses/TimeMeasurer.h"



class MatrixTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( MatrixTest );
    CPPUNIT_TEST( testAddition );
    CPPUNIT_TEST( testMultiplication );
    CPPUNIT_TEST( testTransposition );
  CPPUNIT_TEST_SUITE_END();
  
public:

  void setUp() override;
  void tearDown() override;
  
  void testAddition();
  void testMultiplication();
  void testTransposition();
  
private:
  
  typedef mpz_class Element;
  
  MatrixRandomFiller filler;
  MatrixSummarizer summarizer;
  MatrixMultiplier multiplier;
  MatrixTransposer transposer;
  
  TimeMeasurer timeMeasurer;
  
  std::size_t matrixSize = 50;
};



#endif // MATRIX_TEST
