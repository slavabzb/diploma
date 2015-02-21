#ifndef CONSTRUCTION_TEST
#define CONSTRUCTION_TEST

#include <cppunit/TestCase.h>

class ConstructionTest : public CppUnit::TestCase
{
public:
  ConstructionTest( const std::string& testName );
  void runTest() override;
};

#endif // CONSTRUCTION_TEST
