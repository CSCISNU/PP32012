#include <stdlib.h>
#include <stdio.h>
#include "basetypes.h"

/* Mokuteki: start ni hajimari, required jikan no jikkou wo suru, atarashi process no PCB wo tukuri, sore wo kaesu */
PCB *pcb_new (int start, int required)
{
  PCB *pcb = (PCB *)malloc(sizeof(PCB));
  pcb->next = NULL;
  pcb->pid = 0;			/* 1 */
  pcb->state = READY;
  pcb->waiting_time = 0;
  pcb->executed_time = 0;
  pcb->start_time = start;	 /* 2 */
  pcb->required_time = required; /* 3 */
  return pcb;
}

/* Mokuteki:  q no saigo ni pcb wo tuika suru. return void */
void pcb_enqueue(PCB *pcb, PCB **q)
{
  if (*q == pcb) {
    printf("hen!!!\n");
    exit(0);
  }
  pcb->next = NULL;
  if (! *q)
    *q = pcb;
  else {
    PCB *p = *q;
    while (p->next != NULL) {
      p = p->next;
    }
    if (p->next == pcb) {
      printf("hen!!!\n");
      exit(0);
    }
    p->next = pcb;
  }
}

/* Mokuteki:  q no sentou no PCB wo return site, q ha sentou no ikko wo totta nokori ni naru */
PCB *pcb_dequeue(PCB **q)
{
  PCB *pcb;
  if (! q)
    return NULL;
  pcb = *q;
  *q = pcb; /* FIXME */
  pcb->next = NULL;
  return pcb;
}

/* Mokuteki: q no nakakara pcb wo sagashite sakujo suru */
void pcb_remove(PCB *pcb, PCB **q)
{
  PCB *next, *base;
  if (*q == NULL){		/* tokubetu na baai 1 */
      return;
  }
  if (*q == pcb) {		/* tokubetu na baai 2 */
      *q = (*q)->next;
      return;
  }
  base = *q;
  next = base->next;
  while (next != NULL) {
    if(pcb == next) {
      base->next = next; /* FIXME */
      next = next->next->next;/* FIXME */
      next->next = NULL;
      continue;
    } else {
      base = next;
      next = next->next;
    }
  }
}

/* Mokuteki: q no nakakara start_time ga t no monowo subete sakujo suru */
void pcb_removeAllStartFrom(int t, PCB **q)
{
  PCB *next, *base;
  if (*q == NULL){
      return;
  }
  base = *q;
  next = base->next;
  while (next != NULL) {
    if(next->start_time == t) {
      base->next = next;
      next = next->next->next;
      next->next = NULL;
      break;
    } else {
      base = next;
      next = next->next;
    }
  }
}

/* Mokuteki: PCB no queue no sentou top ga ataeraretara queue no juni PCB wo hyouji suru */
void pcb_print_list(PCB *top)
{
  if (top == NULL) {
    printf("[]");
  }
  else {
    while(top != NULL){
      printf("[pid%d,%d,%d]", top->pid, top->start_time, top->required_time);
      top=top->next;
      if (top)
	printf(", ");
    }
  }
  printf("\n");
}
