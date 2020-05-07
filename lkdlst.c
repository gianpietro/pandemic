#include <stdlib.h>
#include <stdio.h>

#include "lkdlst.h"

int coName = 25;                /* issue with using #define COUNTRY
//#define COUNTRY 25

/*
struct country {
  char nation[COUNTRY];
  int tcases;
  int tdeaths;
  int recdate;
  struct country *next;
};
*/
//extern country country;


struct country *createCountry(char countryname[], int rcdate,  int totcases, int totdeaths) {
  struct country *ptr;
  int i;

  ptr = (struct country *) malloc(sizeof(struct country));

  for (i=0; i<coName; i++)
     ptr->nation[i] = countryname[i];
  ptr->tcases = totcases;
  ptr->tdeaths = totdeaths;
  ptr->recdate = rcdate;
  ptr->next = NULL;

  return ptr;
}
