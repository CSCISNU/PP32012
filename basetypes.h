#define BASETYPES_H

typedef int boolean;
#define true	(1 == 1)
#define false	0

typedef enum { RUNNING, READY, WAITING } Pstate;

/* Process Control Block */
typedef struct PCB {
  struct PCB *next;
  int pid;			/* Process ID */
  Pstate state;			/* joutai */
  int waiting_time;		/* jikkoumachi deno keika jikan */
  int executed_time;		/* jikkou zumi jikan */
  int start_time;		/* seisei jikoku */
  int finished_time;		/* shuryo jikoku */
  int required_time;		/* hituyou jikan */
} PCB;

/* PCB comparing function type */
typedef PCB *(pcb_compare_function)(PCB *, PCB *);

PCB *pcb_new(int, int);
void pcb_enqueue(PCB *, PCB **);
PCB *pcb_dequeue(PCB **);
void pcb_remove(PCB *, PCB **);
void pcb_print_list(PCB*);

int current_clock;
