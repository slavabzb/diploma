#include "ParallelHandler.h"



ParallelHandler::ParallelHandler( std::size_t minNumThreads, std::size_t minPerThread )
{
  this->setMinNumThreads( minNumThreads );
  this->setMinPerThread( minPerThread );
  this->parallelPolicy = policy_automatic;
}



ParallelHandler::ParallelPolicy ParallelHandler::getParallelPolicy() const
{
  return this->parallelPolicy;
}



std::size_t ParallelHandler::getHardwareThreads() const
{
  return this->hardwareThreads;
}



std::size_t ParallelHandler::getMinPerThread() const
{
  return this->minPerThread;
}



std::size_t ParallelHandler::getMinNumThreads() const
{
  return this->minNumThreads;
}



void ParallelHandler::setAutoParallelPolicy()
{
  this->parallelPolicy = policy_automatic;
}



void ParallelHandler::setDirectParallelPolicy( std::size_t numThreads )
{
  this->setNumThreads( numThreads );
  this->userDefinedNumThreads = numThreads;
  this->parallelPolicy = policy_direct;
}



void ParallelHandler::setMinPerThread( std::size_t minPerThread )
{
  assert( minPerThread > 0 );
  
  this->minPerThread = minPerThread;
}



void ParallelHandler::setMinNumThreads( std::size_t minNumThreads )
{
  assert( minNumThreads > 0);
  
  this->minNumThreads = minNumThreads;
}



void ParallelHandler::setUp( std::size_t size )
{
  switch( this->parallelPolicy ) {
    case policy_automatic :
      this->autoCalculateNumThreads( size );
      break;
      
    case policy_direct :
      this->setNumThreads( this->userDefinedNumThreads );
      break;
  }

  this->threads.reserve( this->getNumThreads() - 1 );
}



void ParallelHandler::cleanUp()
{
  std::for_each( this->threads.begin(), this->threads.end(), std::mem_fn( &std::thread::join ) );
  this->threads.clear();
}



void ParallelHandler::setNumThreads( std::size_t numThreads )
{
  assert( numThreads > 0 );

  this->numThreads = numThreads;
}



std::size_t ParallelHandler::getNumThreads() const
{
  return this->numThreads;
}



void ParallelHandler::autoCalculateNumThreads( std::size_t size )
{
  const std::size_t maxThreads = ( size + this->minPerThread - 1 ) / this->minPerThread;
  const std::size_t hardwareBasedEstimate = ( this->hardwareThreads == 0 ?
    this->minNumThreads : this->hardwareThreads );

  this->setNumThreads( std::min( hardwareBasedEstimate, maxThreads ) );
}



