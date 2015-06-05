#ifndef PARALLEL_HANDLER
#define PARALLEL_HANDLER

#include <algorithm>
#include <assert.h>
#include <thread>
#include <vector>



/**
 * A parallel execution controller.
 */
class ParallelHandler
{
public:

  /**
   * Define how the number of threads will be calculated.
   */
  enum class ParallelPolicy
  {
    Automatic,  /**< Calculating based on size of matrix passed to process.  */
    Direct      /**< User defined number of threads.                         */
  };



  /**
   * A default constructor.
   * Configures the controller according to the given values.
   * @param min_num_threads a minimal number of threads used to parallel
   * execution.
   * @param min_per_thread a minimal number of the rows of the matrix processed
   * by single thread.
   */
  ParallelHandler( std::size_t min_num_threads = 2,
    std::size_t min_per_thread = 25 );



  /**
   * Applies the function parallel to the range [first, last].
   * @param first an iterator points to the begin of the range.
   * @param last an iterator points to the end of the range.
   * @param function a function to apply.
   * @warning The function must be equivalent to the following:
   * [return type] function( std::size_t begin, std::size_t end ).
   */
  template< typename Iterator, typename Function >
  void parallel_for( const Iterator& first,
    const Iterator& last,
    Function&& function )
  {
    const std::size_t size = ( last - first );
    if( size == 0 ) {
      return;
    }
    
    this->set_up( size );
    
    const std::size_t chunk_size = size / this->get_num_threads();
    Iterator begin = first;
    for( std::size_t thread = 0;
      thread < ( this->get_num_threads() - 1 ); ++thread ) {
        Iterator end = begin;
        end += chunk_size;
        this->threads[ thread ] = std::thread( function, begin, end );
        begin = end;
    }

    function( begin, last );

    this->clean_up();
  }



  ParallelPolicy get_parallel_policy() const;
  std::size_t get_hardware_threads() const;
  std::size_t get_min_per_thread() const;
  std::size_t get_min_num_threads() const;
  
  void set_auto_parallel_policy();
  void set_direct_parallel_policy( std::size_t num_threads );
  void set_min_per_thread( std::size_t min_per_thread );
  void set_min_num_threads( std::size_t min_num_threads );



private:

  void set_up( std::size_t size );
  void clean_up();
  
  void set_num_threads( std::size_t num_threads );
  std::size_t get_num_threads() const;
  
  void calculate_num_threads( std::size_t size );



  std::vector< std::thread > threads;

  ParallelPolicy parallel_policy;

  const std::size_t hardware_threads;
  
  std::size_t num_threads;
  std::size_t user_defined_num_threads;
  std::size_t min_per_thread;
  std::size_t min_num_threads;
};



#endif // PARALLEL_HANDLER
