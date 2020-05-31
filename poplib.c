#include <stdio.h>
#include <stdlib.h>

#include "poplib.h"

int ctName = CTNAME;


struct population *popCreateCountry(char countryname[], int tpop){

  struct population *ptr;
  int i;

  ptr = (struct population *) malloc(sizeof(struct population));

  for (i=0; i<ctName; i++)
     ptr->nation[i] = countryname[i];
  ptr->tpop = tpop;
  ptr->next = NULL;

  return ptr;
}

struct population *popAppend(struct population *end, struct population *newpt) {
  end->next = newpt;
  return (end->next);
}

void popPrintCountry(struct population *start) {
  struct population *ptr;
  ptr = start;
  int count = 0;

  while (ptr != NULL) {
    printf("country %s, population %d\n",
	   ptr->nation, ptr->tpop);
    ptr = ptr->next;
    count++;
  }
  printf("NUMBER OF RECORDS %d\n", count);
}
