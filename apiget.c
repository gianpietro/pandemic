#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apiget.h"

int apiName = APICOUNTRY;

struct apiGetData *apiCreateCountry(char apiCountry[], char apiCode[], int apiNewCases, int apiTotCases, int apiNewDeaths, int apiTotDeaths, char apiRecDate[], int apiUpDate){
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
  ptr->apiRequiredDate = 0;
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
    printf("Country %s, code %s, new cases %d, totcases %d, new deaths %d, totdeaths %d, date %d\n",
	   ptr->apiCountryName, ptr->apiCountryCode, ptr->apiNewConfirmed, ptr->apiTotalConfirmed, ptr->apiNewDeathsConfirmed, ptr->apiTotalDeaths, ptr->apiRequiredDate);
    ptr = ptr->next;
    apicount++;
  }
  printf("Number of API Records %d\n", apicount);
}

void apiCorrectDate(struct apiGetData *start, int fileUploadDate){
  struct apiGetData *ptr = start;
  while (ptr != NULL){
    ptr->apiRequiredDate = fileUploadDate;
    ptr = ptr->next;
  }
}

void apiCorrectCountryName(struct apiGetData *start, struct apiAlias *aliasStart, int acount){
  struct apiGetData *ptr = start;
  struct apiAlias *aptr = aliasStart;
  int ac;
  while (ptr != NULL) {
    for (ac=0; ac<acount; ac++){
      while (aptr != NULL) {
        if(strcmp(ptr->apiCountryCode, aptr->apiCoAlias) == 0) {
	  strcpy(ptr->apiCountryName, aptr->apiCoName);
	  aptr = aptr->next;
	 }
	 else { 
	   aptr = aptr->next;
	 }
     }
     aptr = aliasStart;
    }
    ptr = ptr->next;
  }
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

struct apiAlias *apiCreateAliasList(char apiC[], char apiA[]){
  struct apiAlias *ptr;
  int i;

  ptr = (struct apiAlias *) malloc(sizeof(struct apiAlias));

  for (i=0; i<apiName; i++)
    ptr->apiCoName[i] = apiC[i];
  for (i=0; i<3; i++)
    ptr->apiCoAlias[i] = apiA[i];
  ptr->next = NULL;

return ptr;
}

struct apiAlias *apiAliasAppend(struct apiAlias *end, struct apiAlias *newpt) {
  end->next = newpt;
  return (end->next);
}

void apiPrintAlias(struct apiAlias *start){
  struct apiAlias *ptr = start;
  int aCount;

  while (ptr != NULL){
    printf("Name %s alias %s\n", ptr->apiCoName, ptr->apiCoAlias);
    ptr = ptr->next;
    aCount++;
  }
  printf("Alias count %d\n", aCount);
}

char **apiDataDate(struct apiGetData *start) {
  struct apiGetData *ptr = start;
  char **dateStr;
  int i = 0;
 
  dateStr = malloc(sizeof(char*));
  // while (ptr != NULL) {
  dateStr[i] = malloc(21*sizeof(char));
  strcpy(dateStr[i], ptr->apiUploadDate);
  //printf("date %s\n", dateStr[i]);
  // ptr = ptr->next;
  //i++;
  // }

  return dateStr;
}
  
int formatDate(char **dateStr) {
  int i = 0; 
  char apidate[21];
  //char y[5];
  //char m[3];
  //char dd[2];
  char dateformat[8];
  int reqdate;
  
  /*  printf("AFTER COPY STR %s\n", *dateStr);
  printf("elements %c\n", dateStr[0][0]);
  printf("elements %c\n", dateStr[0][1]);
  printf("elements %c\n", dateStr[0][2]); */
  for (i=0; i < 4; i++) {
    // y[i] = dateStr[0][i];
    dateformat[i] = dateStr[0][i];
    //printf("%c", y[i]);
  }
  for (i=5; i<7; i++){
    //m[i] = dateStr[0][i];
    dateformat[i-1] = dateStr[0][i];
    //printf("%c", m[i]);
  }
  for (i=8; i<10; i++){
    //dd[i] = dateStr[0][i];
    dateformat[i-2] = dateStr[0][i];
    //printf("%c", dd[i]);
  }
  dateformat[8] = '\0';

  //  printf("dateformat %s\n", dateformat);

  reqdate = atoi(dateformat);
  //  printf("required date %d\n", reqdate);
  
  return reqdate;
}
				
void apiFreeAlias(struct apiAlias *start){
  struct apiAlias *ptr;
  struct apiAlias *tmp;
  ptr = start;
  while (ptr != NULL){
    tmp = ptr->next;
    free(ptr);
    ptr = tmp;
  }
}


