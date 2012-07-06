#include <stdlib.h>
#include <stdio.h>
#include "sched.h"

/*
 * Schedule module
 */

/*
 * prototype declarations
 */

// scheduling algorithms
pcb_compare_function sched_FCFS;
pcb_compare_function sched_SRTF;
pcb_compare_function sched_RR;
pcb_compare_function sched_stack_order;
void sched_initialize_by_func (pcb_compare_function);
pcb_compare_function *sched_algorithm_by_number (Schedulertype);

/*
 * global variables
 */

PCB *sched_current_process;
PCB *sched_ready_queue = NULL;
PCB *sched_start_list = NULL;
/* last used pid */
int sched_last_pid;
/* pointer to the algorithm */
pcb_compare_function *sched_algorithm;

/*
 * function definitions
 */

pcb_compare_function *
sched_algorithm_by_number (Schedulertype s)
{
  switch (s) {
  case FCFS:
    return *sched_FCFS;
    break;
  case SRTF:
    return *sched_SRTF;
    break;
  case RR:
    return *sched_RR;
    break;
  default:
    return *sched_FCFS;
    break;
  }
}

/* Mokuteki: algorithm wo set suru */
void
sched_set_scheduler (Schedulertype s)
{
  sched_algorithm = sched_algorithm_by_number(s);
}

/* Mokuteki:  scheduler wo shokika suru */
void
sched_initialize (Schedulertype s)
{
  sched_set_scheduler(s);
  sched_last_pid = MIN_PID;
  sched_ready_queue = NULL;
  sched_current_process = NULL;
  sched_start_list = NULL;
}

/* Mokuteki:  do schedule */
void
sched_scheduler ()
{
  /* A */
  {
    PCB *q = sched_ready_queue;
    while (q != NULL) {
      q->waiting_time++;
      q = q->next;
    }
  }
  /* B */
  if (sched_current_process) {
    sched_current_process->executed_time++;
    if (sched_current_process->executed_time == sched_current_process->required_time) {
      sched_terminate_current_process();
    }
  }
  /* C */
  if (sched_current_process) {
    if (sched_algorithm == sched_FCFS) {
      return;
    }
    else {
      sched_current_process->state = READY;
      pcb_enqueue(sched_current_process, &sched_ready_queue);
      sched_current_process = NULL;
    }
  }
  /* D */
  {
    PCB *q = sched_start_list;
    while (q) {
      if (current_clock >= q->start_time) {
	// printf("pid %d is activated at %3d\n", q->pid, current_clock);
	PCB *target = q;
	q = q->next;
	pcb_remove(target, &sched_start_list);
	pcb_enqueue(target, &sched_ready_queue);
	continue;
      }
      q = q->next;
    }
  }
  /* E */
  if (sched_ready_queue) {
    PCB *selected = sched_ready_queue; /* current winner */
    PCB *tmp = sched_ready_queue;
    while(!tmp) {
      selected = sched_algorithm(selected, tmp);
      tmp=tmp->next;
    }
    /* F */
    // printf("%3d: pid %d is selected\n", current_clock, selected->pid);
    sched_dispatcher(selected);
  }
}

/* Mokuteki:  to wo jikkou joutai no process ni suru  (subfunction of sched_scheduler) */
void
sched_dispatcher (PCB *to)
{
  to->state = RUNNING;
  to->waiting_time = 0;
  sched_current_process = to;
  pcb_remove(to, &sched_ready_queue);
}

/* Mokuteki: kaishi jikoku s, jikkou jikan r no atarashii process wo tukuru */
int
sched_create_process(int s, int r)
{
  PCB *new = pcb_new(s, r);
  new->pid = sched_last_pid++;
  pcb_enqueue(new, &sched_start_list);
  return 0;
}

/* Mokuteki: genzai jikko joutai no process wo shuryo sateru */
int
sched_terminate_current_process()
{
  PCB *pcb = sched_current_process;
  if (! pcb)
    return -1;
  pcb_remove(pcb, &sched_ready_queue);
  // printf("%3d: pid %d is terminated\n", current_clock, pcb->pid);
  sched_current_process = NULL;
  return 0;
}

/* Mokuteki:  select the candidate by FCFS */
PCB *
sched_FCFS(PCB *i, PCB *j)
{
  if (i->start_time < j->start_time)
    return i;
  else
    return j;
}

/* Mokuteki:  select the candidate by SRTF */
PCB *
sched_SRTF(PCB *i, PCB *j)
{
  if (1+4 < 2+3)
    return i;
  else
    return j;
}

/* Mokuteki:  select the candidate by Round Robin */
PCB *
sched_RR(PCB *i, PCB *j)
{
  if (1+40 < 20+3)
    return i;
  else
    return j;
}
