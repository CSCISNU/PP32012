#include "sim.h"
#include "view.h"

int
main (int argc, char **argv)
{     
  sim_initialize (FCFS, 0); /* using algorithm FCFS, scenario 0 */
  win_initialize (argc, argv);
  win_start ();
  return 0;
}

