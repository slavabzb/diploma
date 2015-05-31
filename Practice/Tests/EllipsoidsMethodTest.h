#ifndef ELLIPSOIDS_METHOD_TEST
#define ELLIPSOIDS_METHOD_TEST

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>



class EllipsoidsMethodTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( EllipsoidsMethodTest );
    CPPUNIT_TEST( test_point );
    CPPUNIT_TEST( test_ellipsoids_method );
  CPPUNIT_TEST_SUITE_END();



public:

  void test_point();
  void test_ellipsoids_method();
};



#endif // ELLIPSOIDS_METHOD_TEST
