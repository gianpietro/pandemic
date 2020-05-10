/* Program to record information relating to coronavirus pandemic
for various countries. Information to store number of cases and 
plot a graph using gnuplot 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lkdlst.h"


int main(void) {
  struct country *start, *newCountryPtr, *end, *ptr;
  char name[COUNTRY];
  char s[COUNTRY];
  int totalcases;
  int totaldeaths;
  int rcdate;
  int n, i;
  int numrec;  /* number of records in date array for country being searched */
  int *arrayDate, *arrayCo;
  int m;
  int *arraytcases;
  int choice = 0;
  
  FILE *fp;
 
  fp = fopen("datafile.txt", "r");

  if (fp == NULL) {
    fprintf(stdout,"\nError opening file\n");
    exit(1);
  }

  while (fscanf(fp, "%s %d %d %d", name, &rcdate, &totalcases, &totaldeaths) != EOF) {
    if (i == 0) {
      start = createCountry(name, rcdate, totalcases, totaldeaths);                                                   
      end = start;
    } else {
      newCountryPtr = createCountry(name, rcdate, totalcases, totaldeaths);
      end = append(end, newCountryPtr);
    }       
    i++;
  }
 
  fclose(fp);

  do {
    printf("Option 1: Display all data from file\n\n");
    printf("Option 2: Graph Total Cases by Country\n\n");
    printf("Option 3: Exit\n");
    // printf("99. Exit\n");    
    printf("Select option: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
       /* print struct content of linked list */ 
       printCountry(start);
       break;
    case 2:
          

       /*
  printf("exit option ");
  int e;
  scanf("%d",&e);
  if (e == 9){
    exit(0);
  }
       */
  
  /* search for a particular country and print the values in its struct */
  printf("Search for a country: ");
  scanf("%s", s);
  searchCountry(start,s);

  
  /* pulls back the number of records for thecountry searched */
  numrec = getCoRec(start,s);                           
  printf("number of record %d\n", numrec);

  /* builds an array of the dates found for the country searched, 
     this will be number of data rows 
     The dates will have been sorted in ascending order */  
  arrayDate = getCoRecdate(start,s,numrec);
    for (m=0; m<numrec;m++){
    printf("record date %d\n",arrayDate[m]);
  }

  arraytcases =  filterCo(start, s, arrayDate, numrec);
  for (i=0; i<numrec; i++) 
    printf("total cases %d\n", arraytcases[i]);
    
  countryGraph(arrayDate, arraytcases, numrec, s);     


  free(arraytcases);
  free(arrayDate);  
  /* free up memory initialised by malloc in create struct*/
  break;
    case 3:
freeCountry(start);
 exit(0);
  break;

    }
  } while (choice != 99);
  return 0;
}


  
  
  



	  
       

      
