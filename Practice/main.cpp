#include "Matrix.h"

#include "Tests/MatrixTest.h"

#include <cppunit/TestResult.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>



int main( int argc, const char* argv[ ] )
{
  CppUnit::TestResult controller;
  
  CppUnit::TestResultCollector result;
  controller.addListener( &result );
  
  CppUnit::TextTestProgressListener progress;
  controller.addListener( &progress );
  
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
  
  runner.run( controller, "" );
  
  CppUnit::CompilerOutputter outputter( &result, std::cerr );
  outputter.write();
  
  return result.wasSuccessful() ? 0 : 1;
}
