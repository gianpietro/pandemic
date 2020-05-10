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
  char c[COUNTRY];
  int totalcases;
  int totaldeaths;
  int rcdate;
  int n, i;
  int numrec;  /* number of records in date array for country being searched */
  int *arrayDate;
  int m;
  int *arraytcases;
  int *arraydcases;
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
    printf("\n");
    printf("Option 1: Display all data from file\n\n");
    printf("Option 2: Graph Total Cases by Country\n\n");
    printf("option 3: Graph Total Deaths by Country\n\n");
    printf("Option 4: Total Cases and Deaths by Country\n\n");
    printf("Option 9: Exit\n\n");
    printf("\n");
    printf("Select option: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        /* print struct content of linked list */ 
        printCountry(start);
        break;
      case 2:
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
	arraydcases =  filterDCo(start, s, arrayDate, numrec);
	countryGraph(arrayDate, arraydcases, numrec, s);
        free(arraydcases);
        free(arrayDate); 
      break;
    case 4:
      printf("Search for a country: ");
        scanf("%s", s);
        searchCountry(start,s);
	numrec = getCoRec(start,s);
	arrayDate = getCoRecdate(start,s,numrec);
	for (m=0; m<numrec;m++){
          printf("record date %d\n",arrayDate[m]);
        }
        arraytcases =  filterCo(start, s, arrayDate, numrec);
	arraydcases =  filterDCo(start, s, arrayDate, numrec);
	countryGraphTotDC(arrayDate, arraytcases, arraydcases, numrec, s);
	free(arraytcases);
	free(arraydcases);
        free(arrayDate); 
      break;
    case 9:
      freeCountry(start);
      exit(0);
      break;
    }
  } while (choice != 99);

  return 0;
}


  
  
  



	  
       

      
