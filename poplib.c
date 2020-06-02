#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "poplib.h"

int ctName = CTNAME;


struct population *popCreateCountry(char countryname[], int tpop){
  struct population *ptr;
  int i;
  int *perPopArray;

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
    printf("country %s, population %d\n", ptr->nation, ptr->tpop);
    ptr = ptr->next;
    count++;
  }
  printf("NUMBER OF RECORDS %d\n", count);
}

double * infectionPercent(struct population *start, char ** icountryArray, int * icasesArray, int idatenum) {
  struct population *ptr = start;
  int i = 0;
  double *perc; 

  perc = malloc(idatenum*sizeof(double));
  
  for (i=0; i<idatenum; i++){
    while (ptr != NULL){
      if (strcmp(icountryArray[i], ptr->nation) == 0){
        perc[i] = (icasesArray[i]/(double)ptr->tpop)*100;
	printf("country: %s pop %d cases: %d rate: %2.5f\n",icountryArray[i], ptr->tpop, icasesArray[i], perc[i]);
	ptr = ptr->next;
       } else {
        ptr = ptr->next;
      }
    }
    ptr = start;
  }
  return perc;
}

	  

		  
      
    


