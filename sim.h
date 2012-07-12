#define SIM_H
#ifndef SCHED_H
#include "sched.h"
#endif 

void sim_initialize (Schedulertype, int);
void sim_start (int);
void sim_print_result(void);

