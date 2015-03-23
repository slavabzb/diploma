#ifndef MATRIX_TEST
#define MATRIX_TEST

#include <memory>

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Matrix.h"

#include "HelperClasses/HelperClasses.h"



class MatrixTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( MatrixTest );
  
  CPPUNIT_TEST( testAddition );
  CPPUNIT_TEST( testMultiplication );
  CPPUNIT_TEST( testScalarMultiplication );
  CPPUNIT_TEST( testTransposition );
  
  CPPUNIT_TEST_SUITE_END();
  
public:

  MatrixTest();

  void setUp() override;
  void tearDown() override;
  
  void testAddition();
  void testMultiplication();
  void testScalarMultiplication();
  void testTransposition();
  
private:
  
  typedef double Element;
  
  std::size_t nIterations;
  std::size_t initialSize;
  std::size_t sizeStep;
  
  MatrixPrinter printer;
  MatrixRandomFiller filler;
  MatrixSummarizer summarizer;
  MatrixMultiplier multiplier;
  MatrixTransposer transposer;
};

#endif // MATRIX_TEST
