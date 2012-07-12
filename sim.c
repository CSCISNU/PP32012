#include <stdio.h>
#include "sim.h"

int sim_set_scenario (int);
int sim_create_process (int s, int t);

/*
 * function definitions
 */
void
sim_initialize (Schedulertype i, int s)
{
  current_clock = 0;
  sched_initialize(i);
  sim_set_scenario(s);
  monitor_initialize();
}

int
sim_create_process (int s, int t)
{
  return sched_create_process(s, t);
}

int
sim_set_scenario (int i)
{
  /* samples */
  switch (i) {
  case 0:
    sim_create_process(0,3);
    sim_create_process(0,1);
    sim_create_process(3,4);
    sim_create_process(5,3);
    sim_create_process(7,1);
    sim_create_process(11,3);
    break;
  case 1:
    sim_create_process(0,1);
    break;
  case 2:
    sim_create_process(0,1);
    sim_create_process(0,1);
    break;
  case 3:
    sim_create_process(0,1);
    sim_create_process(0,2);
    sim_create_process(1,2);
    break;
  case 4:
    sim_create_process(0,2);
    sim_create_process(0,1);
    sim_create_process(1,2);
    break;
  case 5:
    sim_create_process(0,2);
    sim_create_process(3,2);
    sim_create_process(1,2);
    sim_create_process(1,2);
    break;
  case 6:
    sim_create_process(3,2);
    sim_create_process(1,2);
    sim_create_process(1,2);
    sim_create_process(4,2);
    sim_create_process(7,2);
    break;
  case 7:
  default:
    sim_create_process(0,1);
    sim_create_process(1,2);
    sim_create_process(0,3);
    sim_create_process(3,2);
    sim_create_process(1,2);
    sim_create_process(1,2);
    sim_create_process(4,2);
    sim_create_process(7,2);
    break;
  }
  return i;
}

void
sim_start (int upper)
{
  // printf("upper=%d\n", upper);
  while(upper--) {
    sched_scheduler();
    current_clock++;
  }
}

/* Purpose ：print the results of simulation */
void
sim_print_result ()
{
  int pid;
  int t;
  PCB **table;
   printf ("Elapsed time: %d\n", current_clock);
  printf ("Ave. turn-around time: %3.2f\n", monitor_average_turnaround_time ());
  table = monitor_allocation_history();

  for (t = 0; table[t] != NULL; t++) {
    // printf("%d:%d,", t, table[t]->pid);
    printf("%d,", table[t]->pid);
  }
  printf("\n");
  for (pid = 1; pid < sched_last_pid; pid++) {
    printf("%2d :", pid);
    for (t = 0; table[t] != NULL; t++) {
      if (table[t]->pid == pid)
	printf("X");
      else
	printf(" ");
    }
    printf("\n");
  }
}

