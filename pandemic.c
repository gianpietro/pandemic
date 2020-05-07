/* Program to record information relating to coronavirus pandemic
for various countries. Information to store number of cases and 
various outcomes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lkdlst.h"

//country country;
//#define COUNTRY 25

/*struct country {
  char nation[COUNTRY];
  int tcases;
  int tdeaths;
  int recdate;
  struct country *next;
  }; */

/* function prototypes */

/* in seperate file lkdlst.c with header lkdlst.h */
/*******************************************************/
//struct country *createCountry(char *,int, int, int);

struct country *append(struct country *, struct country *);
int getCoRec(struct country *, char *);
int * getCoRecdate(struct country *, char *, int);
//void filteredPtr(struct country *, char *);
//void filterCo(struct country *, char *, int *, int);
int * filterCo(struct country *, char *, int *, int);
void searchCountry(struct country *, char *);
void printCountry(struct country *);
void freeCountry(struct country *);
void countryGraph(int *, int *, int, char *);

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

  //  fstart = start;
  
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
  
  /* print struct content of linked list */ 
  printCountry(start);

  
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

  //filteredPtr(start, s);

  
  //printCountry(start);
  
  //for (m=0; m<numrec;m++){
  //printf("countryFilter %s\n", filter->nation);
  // }
    
  countryGraph(arrayDate, arraytcases, numrec, s);     
  
  free(arraytcases);
  free(arrayDate);  
  /* free up memory initialised by malloc in create struct*/
  freeCountry(start);

  return 0;
}

/* in seperate file lkdlst.c with header lkdlst.h */
/******************************************************* 
  struct country *createCountry(char countryname[COUNTRY], int rcdate,  int totcases, int totdeaths) {
  struct country *ptr;
  int i;

  ptr = (struct country *) malloc(sizeof(struct country));

  for (i=0; i<COUNTRY; i++)
     ptr->nation[i] = countryname[i];
  ptr->tcases = totcases;
  ptr->tdeaths = totdeaths;
  ptr->recdate = rcdate;
  ptr->next = NULL;

  return ptr;
}
*/

/* add new struct to end of linked list */
struct country *append(struct country *end, struct country *newpt) {
  end->next = newpt;
  return (end->next);
}

void printCountry(struct country *start) {
  struct country *ptr;
  ptr = start;
  while (ptr != NULL) {
    printf("country %s, date %d, total cases %d, total deaths %d\n", ptr->nation,ptr->recdate, ptr->tcases, ptr->tdeaths);
    ptr = ptr->next;
  }
}

/* free up malloc memory initaied with createCountry */
void freeCountry(struct country *start) {
  struct country *ptr;
  struct country *tmp;
  ptr = start;
  while (ptr != NULL) {
    tmp = ptr->next;
    free(ptr);
    ptr = tmp;
  }
}

/* search for a specific country and display struct values. The country may have
   multiple entries*/
void searchCountry(struct country *start, char countryname[COUNTRY]) {
  struct country *ptr = start;
  int c = 0;
  while (ptr != NULL) {
    if (strcmp(ptr->nation, countryname) == 0) {
      printf("Country %s date %d totcases %d totdeaths %d\n", ptr->nation, ptr->recdate, ptr->tcases, ptr->tdeaths);
	ptr = ptr->next;
	c++;
      } else {
	ptr = ptr->next;
      }
      }
    if (c ==0)
      printf("Country not found\n");    
  }

/* ABANDONED 

void filteredPtr(struct country *start, char countryname[COUNTRY]) {
  struct country *ptr = start;
  struct country *newCountryPtr, *end, *filter;
  int i;
    //;  struct country *ptr = start;
 
  int c = 0;
   while (ptr != NULL) {
     //     printf("where are we %s\n", ptr->nation);
    if (strcmp(ptr->nation, countryname) == 0) {
      printf("where are we %d\n", ptr->tdeaths);
         printf("value of c %d\n", c);
       if (c == 0) {
         ptr = createCountry(ptr->nation, ptr->recdate, ptr->tcases, ptr->tdeaths);
         end = start;
	 printf("first nation %s\n ", ptr->nation);
	 c++;
        } else {
          newCountryPtr = createCountry(ptr->nation, ptr->recdate, ptr->tcases, ptr->tdeaths);
          end = append(end, newCountryPtr);
	  printf("next nation %s\n ", end->nation);
	  //ptr = ptr-> next;
        }   
       //ptr = ptr->next;
       //printf("where are we new %s\n", ptr->nation);
       //c++;
	//} else {  
	ptr = ptr->next;
	//c++;
    } else {
      ptr = ptr->next;
    }
    
    //  return ptr;
    }
}

*/

/*Loop though the struct and for each record matching country search increate counter
at the end return the number of records found */
int getCoRec(struct country *start, char countryname[COUNTRY]) {
  struct country *ptr = start;
  int c = 0;
  while (ptr != NULL) {
    if (strcmp(ptr->nation, countryname) == 0) {
	ptr = ptr->next;
	c++;
      } else {
	ptr = ptr->next;
      }
      }
  return c;
  }

/* Loop through the struct seaching for country and add recdate values to array using
   number of records found with getCoRec() to increase size of array with malloc.  
   This is a dynamic array. */
int * getCoRecdate(struct country *start, char countryname[COUNTRY], int z) {
  struct country *ptr = start;
  int *recdt;
  //int k = 0;
  int j = 0;
  int i;
  int gap, a, b, temp;
  //int m;
  int k = z;
  /* once number of values for a country found allocate the size to the array recdt */
  recdt = (int *)malloc(k * sizeof(int));
  
  /* now that dynamic array has been allocated the correct size of memory, assign the
     date values for the country */
  ptr = start;
  while (ptr != NULL) {
    if (strcmp(ptr->nation, countryname) == 0) {
      recdt[j] = ptr->recdate;
      ptr = ptr->next;
      j++;
    } else {
      ptr = ptr->next;
    }
  }
  for (i=0; i<k; i++){
    printf("date for country %d\n", recdt[i]);
  }
  /* use a shellsort to arrange the date values in ascending order */
  for (gap = k/2; gap > 0; gap /=2) {
    for (a=gap; a<k; a++) {
     for (b=a-gap; b>=0 && recdt[b]>recdt[b+gap]; b-=gap){
	temp = recdt[b];
        recdt[b] = recdt[b+gap];
        recdt[b+gap] = temp;
	}
    }
   }
  return recdt;
}

/*
void filterCo(struct country *start, char countryname[COUNTRY], int *date, int n){
  struct country *ptr = start;
  struct country *dptr = start; 
  int *fdate = date;
  int *ftc;
  int *fdt;
  int i;
  int j = n;
  while (ptr != NULL) {
      if (strcmp(ptr->nation, countryname) == 0) {
	while (
	  

	
	printf("COUNTRY %s DATE %d ", ptr->nation, ptr->recdate);
	//       for (i=0; i<j; i++) {
	//if (fdate[i] == dptr->recdate) {
	  ftc[i] = dptr->tcases;
	  ftd[i] = 
	    // fdt[i] = dptr->recdate;
	    printf("date of array %d value of cases %d\n",  ftc[i]);
	  //} //else {
	//  dptr = ptr->next;
	//}
	//}
	//i = 0;
      }
	  ptr = ptr->next;
  }
}
*/

/* This function will match number of cases in struct for country searched against the date value
and build an array with case numbers. This array along with recdate array is then used for the x and y
axis of a graph. The values are piped to gnuplot application. If a country has only one data value in the 
record file then this has to be identified or there are issues with array structures.
The graph will draw using lines to join y values unless only one data item which will plot with a point.
*/ 

int * filterCo(struct country *start, char countryname[COUNTRY], int *arrayDate, int numrec) {
  struct country *ptr = start;
  int i = 0;
  int j = numrec;
  //int totalc[j];
  int *totalc;
  int *arrdate = arrayDate;   //not using this can delete

  totalc = (int *)malloc(numrec * sizeof(int)); 
  printf("arraydate at start %d\n", arrdate[1]);
  printf("start date  %d\n", ptr->recdate);
  printf("VALUE OF J %d\n", j);
    
  //  for (i=0; i<j; i++){
    //    while (ptr != NULL && strcmp(ptr->nation, countryname) == 0 ) {
    //  if (ptr != NULL && strcmp(ptr->nation, countryname) == 0 ) {
  
  if (j > 1) {
  for (i=0; i<j; i++){
    while (ptr != NULL) {
      if (strcmp(ptr->nation, countryname) == 0) {
        if (arrayDate[i] == ptr->recdate) {
  	  totalc[i] = ptr->tcases;
	  printf(" cases %d date %d arraydate %d values of i %d\n", totalc[i], ptr->recdate, arrayDate[i], i);
      }
     }
    ptr = ptr->next;
    }  
  ptr = start;
  //  printf("values of i at end %d\n", i);
  }
  } 

  if (j > 1) {
    ptr = start;
  for (i=0; i<j; i++)
    printf("array totalc values %d\n", totalc[i]);
  } 
  
  if (j == 1) {
     while (ptr != NULL) {
      if (strcmp(ptr->nation, countryname) == 0) {
	//ptr = start;
    totalc[0] = ptr->tcases;
    printf("array totalc values %d\n", totalc[0]);
  }
      ptr = ptr->next;
     }
  }

     
  return totalc;
}
 
void countryGraph(int *arrayDate, int *arraytcases, int numrec, char countryname[COUNTRY]) {
  //int *xvals;
  //int *yvals;
  //int points = pt;  
  char filename[10];
  //char *country = ctry;  
  int i;
  int j;


  //xvals = (int *)malloc(numrec * sizeof(int));
  //yvals = (int *)malloc(numrec * sizeof(int));

  /*
  for (j=0; j<numrec; j++){
    xvals[j] = date[j];
    printf("date for graph %d\n", date[j]);
}

  for (j=0; j<numrec; j++)
    yvals[j] = num[j];

  for (j=0;j<numrec;j++)
    printf("y values %d\n", yvals[j]);
  */

  char * commandsForGnuplot[] = {"plot 'data.temp' with lines"};
  char * commandForGnuplotOne[] = {"plot 'data.temp'"};
  
  FILE *temp = fopen("data.temp", "w");

  FILE * gnuplotPipe = popen("gnuplot -persistent", "w");
  
  for (i=0; i < numrec; i++)
    {
    fprintf(temp, "%d %d \n", arrayDate[i], arraytcases[i]); //Write the data to a temporary file
    }

  if (numrec > 1) {  
    for (i=0; i < 1; i++) {
      fprintf(gnuplotPipe, "set title '%s'\n", countryname);  // this allow me to have a variable title 
      fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
  }
    
    if (numrec == 1) {
      fprintf(gnuplotPipe, "set title '%s'\n", countryname);  // this allow me to have a variable title 
      fprintf(gnuplotPipe, "%s \n", commandForGnuplotOne[0]); //Send commands to gnuplot one by one.
    }
    
}



  
  
  



	  
       

      
