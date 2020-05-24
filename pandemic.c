/* Program to record information relating to coronavirus pandemic
for various countries. Information to store number of cases and 
plot a graph using gnuplot 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lkdlst.h"
#include "mltgrp.h"


int main(void) {
  struct country *start, *newCountryPtr, *end, *ptr;
  char name[COUNTRY];
  char s[COUNTRY];
  char c[COUNTRY];
  int totalcases, totaldeaths, dailycases, dailydeaths;
  int rcdate;
  int n, i;
  int numrec;  /* number of records in date array for country being searched */
  int *arrayDate;
  int m;
  int *arraytcases, *arraydcases;
  int choice = 0;
  int f=0, g, p=0;   /* option 7 */
  char **compare;

  
  FILE *fp;
 
  fp = fopen("datafile.txt", "r");

  if (fp == NULL) {
    fprintf(stdout,"\nError opening file\n");
    exit(1);
  }

  while (fscanf(fp, "%s %d %d %d %d %d", name, &rcdate, &totalcases, &totaldeaths, &dailycases, &dailydeaths) != EOF) {
    if (i == 0) {
      start = createCountry(name, rcdate, totalcases, totaldeaths, dailycases, dailydeaths);                                                   
      end = start;
    } else {
      newCountryPtr = createCountry(name, rcdate, totalcases, totaldeaths, dailycases, dailydeaths);
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
    printf("Option 5: New Day Cases by Country\n\n");
    printf("Option 6: Graph New Deaths by Country\n\n");
    printf("Option 7: Campare countries new cases\n\n");
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
	//type = 2;
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
        arraytcases =  filterCo(start, s, arrayDate, numrec, choice);
        for (i=0; i<numrec; i++) 
          printf("total cases %d\n", arraytcases[i]);
        countryGraph(arrayDate, arraytcases, numrec, s, choice);     
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
	arraydcases =  filterDCo(start, s, arrayDate, numrec, choice);
	countryGraph(arrayDate, arraydcases, numrec, s, choice);
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
        arraytcases =  filterCo(start, s, arrayDate, numrec, choice);
	arraydcases =  filterDCo(start, s, arrayDate, numrec, choice);
	countryGraphTotDC(arrayDate, arraytcases, arraydcases, numrec, s);
	free(arraytcases);
	free(arraydcases);
        free(arrayDate); 
      break;
    case 5:
      //type = 2;
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
        for (m=0; m<numrec; m++){
          printf("record date %d\n",arrayDate[m]);
        }
        arraytcases =  filterCo(start, s, arrayDate, numrec, choice);
        for (i=0; i<numrec; i++) 
          printf("total cases %d\n", arraytcases[i]);
        countryGraph(arrayDate, arraytcases, numrec, s, choice);     
        free(arraytcases);
        free(arrayDate);  
        /* free up memory initialised by malloc in create struct*/
      break;
      case 6:
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
	arraydcases =  filterDCo(start, s, arrayDate, numrec, choice);
	countryGraph(arrayDate, arraydcases, numrec, s, choice);
        free(arraydcases);
        free(arrayDate); 
      break;
    case 7:
      printf("Number of countries to compare (max is 5): ");
      scanf("%d", &f);
      //      compare = malloc(f*sizeof(char*));      /* malloc for number of countries to compare */
      if (f <= 5){
	compare = malloc(f*sizeof(char*));      /* malloc for number of countries to compare */
        for (g=0; g<f; g++){
          printf("Enter country ");
	  scanf("%s", s);	
	  compare[g] = malloc(COUNTRY*sizeof(char));    /* malloc for char length of country name */
	  strcpy(compare[g], s);
	  printf("compare %s\n", compare[g]);
	} 
	//for (g=0; g<f; g++){
	//printf("compare countries %s\n", compare[g]);
	//}
	for (g=0; g<f; g++){
	  strcpy(s, compare[g]);
	  printf("AND NOW compare %s\n", s);  //debug
	  numrec = getCoRec(start, s);
	  printf("numrec in compare %d in country %s\n", numrec, s); //debug
	  arrayDate = getCoRecdate(start, s, numrec);
	  arraytcases =  filterCo(start, s, arrayDate, numrec, choice);	
	  compareGraph(arrayDate, arraytcases, numrec, s, g);
	  free(arraytcases);
	  free(arrayDate);
	  free(compare[g]);
	}
	buildGraph(g);
	free(compare);	
     }
     break;
    case 9:
      freeCountry(start);
      exit(0);
      break;
    }
  } while (choice != 99);

  return 0;
}


  
  
  



	  
       

      
