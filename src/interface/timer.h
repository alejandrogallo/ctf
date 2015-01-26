#ifndef __TIMER_H__
#define __TIMER_H__

#include "common.h"

namespace CTF {

  /**
   * \defgroup timer Timing and cost measurement
   * @{
   */

  #define MAX_NAME_LENGTH 53
      
  class Function_timer{
    public:
      char name[MAX_NAME_LENGTH];
      double start_time;
      double start_excl_time;
      double acc_time;
      double acc_excl_time;
      int calls;

      double total_time;
      double total_excl_time;
      int total_calls;

    public: 
      Function_timer(char const * name_, 
                     double const start_time_,
                     double const start_excl_time_);
      void compute_totals(MPI_Comm comm);
      bool operator<(Function_timer const & w) const ;
      void print(FILE *         output, 
                 MPI_Comm const comm, 
                 int const      rank,
                 int const      np);
  };


  /**
   * \brief local process walltime measurement
   */
  class Timer{
    public:
      char const * timer_name;
      int index;
      int exited;
      int original;
    
    public:
      Timer(char const * name);
      ~Timer();
      void stop();
      void start();
      void exit();
      
  };

  /**
   * \brief epoch during which to measure timers
   */
  class Timer_epoch{
    private:
      Timer * tmr_inner;
      Timer * tmr_outer;
      std::vector<Function_timer> saved_function_timers;
      double save_excl_time;
      double save_complete_time; 
    public:
      char const * name;
      //create epoch called name
      Timer_epoch(char const * name_);
      
      //clears timers and begins epoch
      void begin();

      //prints timers and clears them
      void end();
  };


  /**
   * \brief a term is an abstract object representing some expression of tensors
   */

  /**
   * \brief measures flops done in a code region
   */
  class Flop_Counter{
    public:
      int64_t  start_count;

    public:
      /**
       * \brief constructor, starts counter
       */
      Flop_Counter();
      ~Flop_Counter();

      /**
       * \brief restarts counter
       */
      void zero();

      /**
       * \brief get total flop count over all counters in comm
       */
      int64_t count(MPI_Comm comm = MPI_COMM_SELF);

  };

}

/**
 * @}
 */

#endif

