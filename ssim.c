#include <stdio.h>
#include "sim.h"

int
main(void)
{
  sim_initialize (FCFS, 0); /* using algorithm FCFS, scenario 0 */
  sim_start (30);	    /* start simulation from clock=0 to clock=30  */
  sim_print_result ();
  return 0;
}

