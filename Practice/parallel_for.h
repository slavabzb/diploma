#ifndef PARALLEL_FOR
#define PARALLEL_FOR

#include <functional>
#include <thread>
#include <vector>



class parallel_for
{
public:

  parallel_for( std::size_t firstRow, std::size_t lastRow,
    std::function< void( std::size_t, std::size_t ) >&& function )
  {  
    const uint64_t nRows =  lastRow - firstRow;
    if( nRows == 0 ) {
      return;
    }

    const uint64_t minRowsPerThread = 25;
    const uint64_t maxThreads = ( nRows + minRowsPerThread - 1 ) / minRowsPerThread;
    const uint64_t hardwareThreads = std::thread::hardware_concurrency() == 0 ?
      2 : std::thread::hardware_concurrency();
    const uint64_t nThreads = std::min( hardwareThreads, maxThreads );
    
    std::vector< std::thread > threads( nThreads - 1 );

    const uint64_t chunkSize = nRows / nThreads;
    std::size_t iFirst = firstRow;
    for( auto iThread = threads.begin(); iThread != threads.end(); ++iThread ) {
      std::size_t iLast = iFirst;
      iLast += chunkSize;
      *iThread = std::thread( function, iFirst, iLast );
      iFirst = iLast;
    }

    function( iFirst, lastRow );

    std::for_each( threads.begin(), threads.end(), std::mem_fn( &std::thread::join ) );
  }
  
};



#endif // PARALLEL_FOR
