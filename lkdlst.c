#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lkdlst.h"

int coName = COUNTRY;                /* issue with using #define COUNTRY */

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


/* add new struct to end of linked list */
struct country *append(struct country *end, struct country *newpt) {
  end->next = newpt;
  return (end->next);
}

/* search for a specific country and display struct values. The country may have
   multiple entries*/
void searchCountry(struct country *start, char countryname[]) {
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


/* Find how many data records there are for a country.
Loop though the struct and for each record matching country search increate counter
at the end return the number of records found */
int getCoRec(struct country *start, char countryname[]) {
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
int * getCoRecdate(struct country *start, char countryname[], int z) {
  struct country *ptr = start;
  int *recdt;
  int j = 0;
  int i;
  int gap, a, b, temp;
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


/* Build array of total case numbers for a country. 
This function will match number of cases in struct for country searched against the date value
and build an array with case numbers. This array along with recdate array is then used for the x and y
axis of a graph. The values are piped to gnuplot application. If a country has only one data value in the 
record file then this has to be identified or there are issues with array structures.
The graph will draw using lines to join y values unless only one data item in which case will plot with a point.
*/ 

int * filterCo(struct country *start, char countryname[], int *arrayDate, int numrec) {
  struct country *ptr = start;
  int i = 0;
  int j = numrec;
  int *totalc;
  //  int *arrdate = arrayDate;   //not using this can delete
  totalc = (int *)malloc(numrec * sizeof(int)); 
  //printf("arraydate at start %d\n", arrdate[1]);
  printf("start date  %d\n", ptr->recdate);
  printf("VALUE OF J %d\n", j);
  
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
        totalc[0] = ptr->tcases;
        printf("array totalc values %d\n", totalc[0]);
     }
      ptr = ptr->next;
     }
  }
  return totalc;
}

void countryGraph(int *arrayDate, int *arraytcases, int numrec, char countryname[COUNTRY]) {
  char filename[10];
  int i;
  int j;

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
