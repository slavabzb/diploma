#ifndef MATRIX_TEST
#define MATRIX_TEST

#include <memory>

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Matrix.h"



class MatrixTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( MatrixTest );
  
  CPPUNIT_TEST( testConstruction );
  CPPUNIT_TEST( testAccessing );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testAddition );
  CPPUNIT_TEST( testMultiplication );
  CPPUNIT_TEST( testTransposition );
  
  CPPUNIT_TEST_SUITE_END();
  
public:

  void setUp() override;
  void tearDown() override;
  
  void testConstruction();
  void testAccessing();
  void testAssignment();
  void testAddition();
  void testMultiplication();
  void testTransposition();
};

#endif // MATRIX_TEST
