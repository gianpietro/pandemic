#include <stdio.h>
#include <stdlib.h>

#include "apiget.h"

int apiName = APICOUNTRY;

struct apiGetData *apiCreateCountry(char apiCountry[], char apiCode[], int apiNewCases, int apiTotCases, int apiNewDeaths, int apiTotDeaths, char apiRecDate[]){
  struct apiGetData *ptr;
  int i = 0;

  ptr = (struct apiGetData *) malloc(sizeof(struct apiGetData));

  for(i=0; i<apiName; i++)
    ptr->apiCountryName[i] = apiCountry[i];
  for(i=0; i<3; i++)
    ptr->apiCountryCode[i] = apiCode[i];
  ptr->apiNewConfirmed = apiNewCases;
  ptr->apiTotalConfirmed = apiTotCases;
  ptr->apiNewDeathsConfirmed = apiNewDeaths;
  ptr->apiTotalDeaths = apiTotDeaths;
  for(i=0; i<22; i++)
    ptr->apiUploadDate[i] = apiRecDate[i];
  ptr->next = NULL;

  return ptr;
}

struct apiGetData *apiAppend(struct apiGetData *end, struct apiGetData *newpt) {
  end->next = newpt;
  return(end->next);
}

void apiPrintCountry(struct apiGetData *start) {
  struct apiGetData *ptr;
  ptr = start;
  int apicount = 0;

  while (ptr != NULL){
    printf("Country %s, code %s, new cases %d, totcases %d, new deaths %d, totdeaths %d, date %s\n",
	   ptr->apiCountryName, ptr->apiCountryCode, ptr->apiNewConfirmed, ptr->apiTotalConfirmed, ptr->apiNewDeathsConfirmed, ptr->apiTotalDeaths, ptr->apiUploadDate);
    ptr = ptr->next;
    apicount++;
  }
  printf("Number of API Records %d\n", apicount);
}

void apiFreeCountry(struct apiGetData *start){
  struct apiGetData *ptr = start;;
  struct apiGetData *tmp;
  //ptr = start;
  while (ptr != NULL){
    tmp = ptr->next;
     free(ptr);
     ptr = tmp;
  }
}



  
			     
