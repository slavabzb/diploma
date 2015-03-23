#include "MatrixTest.h"

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>



CPPUNIT_TEST_SUITE_REGISTRATION( MatrixTest );



MatrixTest::MatrixTest()
  : printer( &std::cout )
{
  this->initialSize = 50;
  this->sizeStep = 50;
  this->nIterations = 9;
}



void MatrixTest::setUp()
{  

}



void MatrixTest::tearDown()
{

}



void MatrixTest::testAddition()
{
  std::size_t size = this->initialSize;
  for( std::size_t iteration = 0; iteration < this->nIterations; ++iteration ) {
    Matrix< Element > A( size, size );
    this->filler.fill( A );
    
    Matrix< Element > B( size, size );
    this->filler.fill( B );
    
    Matrix< Element > C( size, size );
    this->summarizer.sum( C, A, B );
    
    Matrix< Element > D( size, size );
    D = A + B;
    
    CPPUNIT_ASSERT( C == D );
    
    size += this->sizeStep;
  }
}



void MatrixTest::testMultiplication()
{
  std::size_t size = this->initialSize;
  for( std::size_t iteration = 0; iteration < this->nIterations; ++iteration ) {
    Matrix< Element > A( size, size );
    this->filler.fill( A );
    
    Matrix< Element > B( size, size );
    this->filler.fill( B );
    
    Matrix< Element > C( size, size );
    this->multiplier.multiply( C, A, B );
    
    Matrix< Element > D( A * B );
    
    CPPUNIT_ASSERT( C == D );
    
    size += this->sizeStep;
  }
}



void MatrixTest::testScalarMultiplication()
{
  std::size_t size = this->initialSize;
  for( std::size_t iteration = 0; iteration < this->nIterations; ++iteration ) {
    Matrix< Element > A( size, size );
    this->filler.fill( A );
    
    Matrix< Element > B( A );
    Element value = 2;
    this->multiplier.multiply( value, B );
    
    Matrix< Element > C( value * A );
    
    CPPUNIT_ASSERT( B == C );
    
    size += this->sizeStep;
  }
}



void MatrixTest::testTransposition()
{
  std::size_t size = this->initialSize;
  for( std::size_t iteration = 0; iteration < this->nIterations; ++iteration ) {
    Matrix< Element > A( size, size );
    this->filler.fill( A );
    
    Matrix< Element > B( size, size );
    this->transposer.transpose( B, A );
    
    Matrix< Element > C( A.transpose() );
    
    CPPUNIT_ASSERT( B == C );
    
    size += this->sizeStep;
  }
}



