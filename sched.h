#define SCHED_H
#ifndef BASETYPES_H
#include "basetypes.h"
#endif

#define MIN_PID 1		/* PID starts from 1 */

// kind of scheduling algorithm
typedef enum { FCFS, SRTF, RR } Schedulertype;

void sched_pcb_enqueue(PCB *, PCB *);
void sched_initialize_PCB (PCB *, int, int);
void sched_terminate_process(PCB *);
void sched_initialize (Schedulertype);
void sched_scheduler (void);
void sched_dispatcher (PCB *);
boolean sched_all_process_finished ();
int sched_terminate_current_process();
void sched_terminate_process(PCB *);
int sched_create_process(int, int);
void sched_set_scheduler (Schedulertype);

extern PCB *sched_current_process;
extern PCB *sched_ready_queue;
extern PCB *sched_start_list;
extern int sched_last_pid;
extern int current_clock;
