#include "MatrixTest.h"

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "HelperClasses/Logger.h"



CPPUNIT_TEST_SUITE_REGISTRATION( MatrixTest );



MatrixTest::MatrixTest()
{
  this->initialSize = 50;
  this->stepSize = 50;
  this->nIterations = 10;
}



void MatrixTest::setUp()
{  

}



void MatrixTest::tearDown()
{

}



void MatrixTest::testAddition()
{
  Logger::getInstance()->write( "\nAddition" )->write( "\n", 0 );
  
  std::size_t size = this->initialSize;
  for( std::size_t iteration = 0; iteration < this->nIterations; ++iteration ) {
    Logger::getInstance()->write( iteration, 5 )->write( size, 6 );
    
    Matrix< Element > A( size, size );
    this->filler.fill( A );
    
    Matrix< Element > B( size, size );
    this->filler.fill( B );
    
    Matrix< Element > C( size, size );
    this->timeMeasurer.start();
    this->summarizer.sum( C, A, B );
    this->timeMeasurer.end();
    
    double singleThreadTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( singleThreadTime );

    this->timeMeasurer.start();
    Matrix< Element > D( A + B );
    this->timeMeasurer.end();
    
    double multyThreadTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( multyThreadTime );
    
    Logger::getInstance()->write( singleThreadTime / multyThreadTime )->write( "\n", 0 );
    
    CPPUNIT_ASSERT( C == D );
    
    size += this->stepSize;
  }
  
}



void MatrixTest::testMultiplication()
{
  Logger::getInstance()->write( "\nMultiplication" )->write( "\n", 0 );
  
  std::size_t size = this->initialSize;
  for( std::size_t iteration = 0; iteration < this->nIterations; ++iteration ) {
    Logger::getInstance()->write( iteration, 5 )->write( size, 6 );
    
    Matrix< Element > A( size, size );
    this->filler.fill( A );
    
    Matrix< Element > B( size, size );
    this->filler.fill( B );
    
    Matrix< Element > C( size, size );
    this->timeMeasurer.start();
    this->multiplier.multiply( C, A, B );
    this->timeMeasurer.end();
    
    double singleThreadTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( singleThreadTime );
    
    this->timeMeasurer.start();
    Matrix< Element > D( A * B );
    this->timeMeasurer.end();
    
    double multyThreadTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( multyThreadTime );
    
    Logger::getInstance()->write( singleThreadTime / multyThreadTime )->write( "\n", 0 );
    
    CPPUNIT_ASSERT( C == D );
    
    size += this->stepSize;
  }
}



void MatrixTest::testScalarMultiplication()
{
  Logger::getInstance()->write( "\nScalar multiplication" )->write( "\n", 0 );
  
  std::size_t size = this->initialSize;
  for( std::size_t iteration = 0; iteration < this->nIterations; ++iteration ) {
    Logger::getInstance()->write( iteration, 5 )->write( size, 6 );
    
    Matrix< Element > A( size, size );
    this->filler.fill( A );
    
    Matrix< Element > B( A );
    Element value = 2;
    this->timeMeasurer.start();
    this->multiplier.multiply( value, B );
    this->timeMeasurer.end();
    
    double singleThreadTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( singleThreadTime );
    
    this->timeMeasurer.start();
    Matrix< Element > C( value * A );
    this->timeMeasurer.end();
    
    double multyThreadTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( multyThreadTime );
    
    Logger::getInstance()->write( singleThreadTime / multyThreadTime )->write( "\n", 0 );
    
    CPPUNIT_ASSERT( B == C );
    
    size += this->stepSize;
  }
}



void MatrixTest::testTransposition()
{
  Logger::getInstance()->write( "\nTransposition" )->write( "\n", 0 );
  
  std::size_t size = this->initialSize;
  for( std::size_t iteration = 0; iteration < this->nIterations; ++iteration ) {
    Logger::getInstance()->write( iteration, 5 )->write( size, 6 );
    
    Matrix< Element > A( size, size );
    this->filler.fill( A );
    
    Matrix< Element > B( size, size );
    this->timeMeasurer.start();
    this->transposer.transpose( B, A );
    this->timeMeasurer.end();
    
    double singleThreadTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( singleThreadTime );
    
    this->timeMeasurer.start();
    Matrix< Element > C( A.transpose() );
    this->timeMeasurer.end();
    
    double multyThreadTime = this->timeMeasurer.getDurationInSeconds();
    Logger::getInstance()->write( multyThreadTime );
    
    Logger::getInstance()->write( singleThreadTime / multyThreadTime )->write( "\n", 0 );
    
    CPPUNIT_ASSERT( B == C );
    
    size += this->stepSize;
  }
}



