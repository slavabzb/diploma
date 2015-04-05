#ifndef PARALLEL_HANDLER
#define PARALLEL_HANDLER

#include <algorithm>
#include <assert.h>
#include <thread>
#include <vector>



class ParallelHandler
{
public:

  enum ParallelPolicy
  {
    policy_automatic,
    policy_direct
  };



  ParallelHandler( std::size_t minNumThreads = 2, std::size_t minPerThread = 25 );



  template< typename Iterator, typename Function >
  void loop_for( const Iterator& first, const Iterator& last, const Function& function )
  {
    const std::size_t size = ( last - first );
    if( size == 0 ) {
      return;
    }
    
    this->setUp( size );
    
    const std::size_t chunkSize = size / this->getNumThreads();
    Iterator iFirst = first;
    for( auto iThread = this->threads.begin(); iThread != this->threads.end(); ++iThread ) {
      Iterator iLast = iFirst;
      iLast += chunkSize;
      *iThread = std::thread( function, iFirst, iLast );
      iFirst = iLast;
    }

    function( iFirst, last );

    this->cleanUp();
  }



  ParallelPolicy getParallelPolicy() const;
  std::size_t getHardwareThreads() const;
  std::size_t getMinPerThread() const;
  std::size_t getMinNumThreads() const;
  
  void setAutoParallelPolicy();
  void setDirectParallelPolicy( std::size_t numThreads );
  void setMinPerThread( std::size_t minPerThread );
  void setMinNumThreads( std::size_t minNumThreads );



private:

  void setUp( std::size_t size );
  void cleanUp();
  
  void setNumThreads( std::size_t numThreads );
  std::size_t getNumThreads() const;
  
  void autoCalculateNumThreads( std::size_t size );



  std::vector< std::thread > threads;

  ParallelPolicy parallelPolicy;

  const std::size_t hardwareThreads = std::thread::hardware_concurrency();
  
  std::size_t numThreads;
  std::size_t userDefinedNumThreads;
  std::size_t minPerThread;
  std::size_t minNumThreads;
};



#endif // PARALLEL_HANDLER
