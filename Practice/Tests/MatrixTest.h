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
  
  CPPUNIT_TEST_SUITE_END();
  
public:
  void setUp() override;
  void tearDown() override;
  
  void testConstruction();
  void testAccessing();
};

#endif // MATRIX_TEST
