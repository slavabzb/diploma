#ifndef ELLIPSOID_METHOD_TEST
#define ELLIPSOID_METHOD_TEST

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>



class EllipsoidMethodTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( EllipsoidMethodTest );
    CPPUNIT_TEST( testPoint );
    CPPUNIT_TEST( testEllipsoidMethod );
  CPPUNIT_TEST_SUITE_END();



public:

  void testPoint();
  void testEllipsoidMethod();
};



#endif // ELLIPSOID_METHOD_TEST
