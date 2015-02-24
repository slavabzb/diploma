#ifndef MATRIX_TEST
#define MATRIX_TEST

#include <memory>
#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>
#include "Matrix.h"

class MatrixTest : public CppUnit::TestFixture
{
public:
  void setUp() override;
  void tearDown() override;
  
  void testConstruction();
  void testAccessing();
  
  static CppUnit::Test* suite();
};

#endif // MATRIX_TEST
