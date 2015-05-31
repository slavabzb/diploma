#include "ParallelHandler.h"



ParallelHandler::ParallelHandler( std::size_t min_num_threads, std::size_t min_per_thread )
  : hardware_threads( std::thread::hardware_concurrency() )
{
  this->set_min_num_threads( min_num_threads );
  this->set_min_per_thread( min_per_thread );
  this->set_auto_parallel_policy();
}



ParallelHandler::ParallelPolicy ParallelHandler::get_parallel_policy() const
{
  return this->parallel_policy;
}



std::size_t ParallelHandler::get_hardware_threads() const
{
  return this->hardware_threads;
}



std::size_t ParallelHandler::get_min_per_thread() const
{
  return this->min_per_thread;
}



std::size_t ParallelHandler::get_min_num_threads() const
{
  return this->min_num_threads;
}



void ParallelHandler::set_auto_parallel_policy()
{
  this->parallel_policy = ParallelPolicy::Automatic;
}



void ParallelHandler::set_direct_parallel_policy( std::size_t num_threads )
{
  this->set_num_threads( num_threads );
  this->user_defined_num_threads = num_threads;
  this->parallel_policy = ParallelPolicy::Direct;
}



void ParallelHandler::set_min_per_thread( std::size_t min_per_thread )
{
  assert( min_per_thread > 0 );
  
  this->min_per_thread = min_per_thread;
}



void ParallelHandler::set_min_num_threads( std::size_t min_num_threads )
{
  assert( min_num_threads > 0);
  
  this->min_num_threads = min_num_threads;
}



void ParallelHandler::set_up( std::size_t size )
{
  if( this->parallel_policy == ParallelPolicy::Automatic ) {
    this->calculate_num_threads( size );
  }
  else if( this->parallel_policy == ParallelPolicy::Direct ) {
    this->set_num_threads( this->user_defined_num_threads );
  }
  
  this->threads.resize( this->get_num_threads() - 1 );
}



void ParallelHandler::clean_up()
{
  std::for_each( this->threads.begin(), this->threads.end(), std::mem_fn( &std::thread::join ) );
  this->threads.clear();
}



void ParallelHandler::set_num_threads( std::size_t num_threads )
{
  assert( num_threads > 0 );

  this->num_threads = num_threads;
}



std::size_t ParallelHandler::get_num_threads() const
{
  return this->num_threads;
}



void ParallelHandler::calculate_num_threads( std::size_t size )
{
  const std::size_t max_threads = (
    ( size + this->get_min_per_thread() - 1 ) / this->get_min_per_thread()
  );
  const std::size_t hardware_based_estimate = ( this->get_hardware_threads() == 0 ?
    this->get_min_num_threads() : this->get_hardware_threads() );
  
  this->set_num_threads( std::min( hardware_based_estimate, max_threads ) );
}



