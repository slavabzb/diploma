#include "MatrixTest.h"

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "HelperClasses/Logger.h"



CPPUNIT_TEST_SUITE_REGISTRATION( MatrixTest );



void MatrixTest::setUp()
{  

}



void MatrixTest::tearDown()
{

}



void MatrixTest::testAddition()
{  
  Matrix< Element > A( this->matrixSize, this->matrixSize );
  this->filler.fill( A );

  Matrix< Element > B( this->matrixSize, this->matrixSize );
  this->filler.fill( B );

  Matrix< Element > C( this->matrixSize, this->matrixSize );
  this->summarizer.sum( C, A, B );

  Matrix< Element > D( A + B );

  CPPUNIT_ASSERT( C == D );
}



void MatrixTest::testMultiplication()
{
  Matrix< Element > A( this->matrixSize, this->matrixSize );
  this->filler.fill( A );

  Matrix< Element > B( this->matrixSize, this->matrixSize );
  this->filler.fill( B );

  Matrix< Element > C( this->matrixSize, this->matrixSize );
  this->multiplier.multiply( C, A, B );

  Matrix< Element > D( A * B );

  CPPUNIT_ASSERT( C == D );
  
  Matrix< Element > E( A );
  Element value = 2;
  this->multiplier.multiply( value, E );

  Matrix< Element > F( value * A );

  CPPUNIT_ASSERT( A == E );
}



void MatrixTest::testTransposition()
{
  Matrix< Element > A( this->matrixSize, this->matrixSize );
  this->filler.fill( A );

  Matrix< Element > B( this->matrixSize, this->matrixSize );
  this->transposer.transpose( B, A );

  Matrix< Element > C( A.transpose() );
  
  CPPUNIT_ASSERT( B == C );
}



