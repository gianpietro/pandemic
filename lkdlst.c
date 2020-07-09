#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lkdlst.h"

int coName = COUNTRY;               


struct country *createCountry(char countryname[], int rcdate,  int totcases, int totdeaths, int daycases, int daydeaths) {
  struct country *ptr;
  int i;

  ptr = (struct country *) malloc(sizeof(struct country));

  for (i=0; i<coName; i++)
     ptr->nation[i] = countryname[i];
  ptr->tcases = totcases;
  ptr->tdeaths = totdeaths;
  ptr->dcases = daycases;
  ptr->ddeaths = daydeaths;
  ptr->recdate = rcdate;
  ptr->next = NULL;

  return ptr;
}


/* Add new struct to end of linked list */
struct country *append(struct country *end, struct country *newpt) {
  end->next = newpt;
  return (end->next);
}

/* Search for a specific country and display struct values. The country may have
   multiple entries*/
void searchCountry(struct country *start, char countryname[]) {
  struct country *ptr = start;
  int c = 0;
  
  while (ptr != NULL) {
    if (strcmp(ptr->nation, countryname) == 0) {
      printf("Country %s date %d totcases %d totdeaths %d newcases %d newdeaths %d\n ",
	     ptr->nation, ptr->recdate, ptr->tcases, ptr->tdeaths, ptr->dcases, ptr->ddeaths);
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
  int count = 0;

  while (ptr != NULL) {
    printf("country %s, date %d, total cases %d, total deaths %d new cases %d new deaths %d\n",
	   ptr->nation,ptr->recdate, ptr->tcases, ptr->tdeaths, ptr->dcases, ptr->ddeaths);
    ptr = ptr->next;
    count++;
  }
  printf("NUMBER OF RECORDS %d\n", count);
}


/* Free up malloc memory initaied with createCountry */
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
    }
    else {
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

  /* Once number of values for a country found allocate the size to the array recdt */
  recdt = (int *)malloc(k * sizeof(int));
  
  /* Now that dynamic array has been allocated the correct size of memory, assign the
     date values for the country */
  ptr = start;
  while (ptr != NULL) {
    if (strcmp(ptr->nation, countryname) == 0) {
      recdt[j] = ptr->recdate;
      ptr = ptr->next;
      j++;
    }
    else {
      ptr = ptr->next;
    }
  }

  /* Use a shellsort to arrange the date values in ascending order */  
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

int * filterCo(struct country *start, char countryname[], int *arrayDate, int numrec, int choice) {
  struct country *ptr = start;
  int i = 0;
  int j = numrec;
  int *totalc;
  
  totalc = (int *)malloc(numrec * sizeof(int)); 
  
  if (j > 1) {
    for (i=0; i<j; i++){
      while (ptr != NULL) {
        if (strcmp(ptr->nation, countryname) == 0) {
          if (arrayDate[i] == ptr->recdate) {
	    if (choice == 2 || choice == 4) {
	      totalc[i] = ptr->tcases;
	     }
	     else if (choice == 5 || choice == 7) {
	       totalc[i] = ptr->dcases;
	     }	    	 
          }
       }
      ptr = ptr->next;
    }  
    ptr = start;
    }
  } 

  if (j > 1)
    ptr = start;
  
  if (j == 1) {
    while (ptr != NULL) {
      if (strcmp(ptr->nation, countryname) == 0) {
	if (choice == 2 || choice == 4) {
        totalc[0] = ptr->tcases;
	} else if (choice == 5){
	  totalc[0] = ptr->dcases;
	}
      }
      ptr = ptr->next;
     }
  }
  return totalc;
}

/* Total deaths for a country */
int * filterDCo(struct country *start, char countryname[], int *arrayDate, int numrec, int choice) {
  struct country *ptr = start;
  int i = 0;
  int j = numrec;
  int *totalc;
  
  totalc = (int *)malloc(numrec * sizeof(int)); 
  
  if (j > 1) {
    for (i=0; i<j; i++){
      while (ptr != NULL) {
        if (strcmp(ptr->nation, countryname) == 0) {
          if (arrayDate[i] == ptr->recdate) {
	    if (choice == 3 || choice == 4) {
  	      totalc[i] = ptr->tdeaths;
	    } else if (choice == 6){
	      totalc[i] = ptr->ddeaths;
	    }
	  }
       }
      ptr = ptr->next;
    }  
    ptr = start;
    }
  }
  
  if (j > 1) 
    ptr = start;
  
  if (j == 1) {
    while (ptr != NULL) {
      if (strcmp(ptr->nation, countryname) == 0) {
        if (choice == 3 || choice == 4) {
          totalc[0] = ptr->tdeaths;
        } else if (choice == 6) {
            totalc[0] = ptr->ddeaths;
	    }
      }
      ptr = ptr->next;
     }
  }
  return totalc;
}

/* Will plot either total cases or total deaths depending on option selected 
   from menu */
void countryGraph(int *arrayDate, int *arraytcases, int numrec, char countryname[], int choice, int view) {
  char filename[10];
  int i;
  int j;
  int *row;
  int numOfCommands = 8;   /*increase this if number of commands in commandsForGnuplot[] increases */
  int c;

  /*
  char * commandsForGnuplot[]  =
    {"set xtics border out rotate by 90 offset character 0, -2, 0 autojustify",
     "set xtics font ',5'",
     "set ytics font ',6'",
     "set ylabel 'Total number of Cases",
     "set xlabel 'Date'",
     "set grid",
     "unset key",
     "plot for [i=2:2] 'data.temp' using i:xtic(1) lw 1.5 smooth mcsplines"};
  */

   
  char commandsForGnuplot[8][200];
  // strcpy(commandsForGnuplot[0],"set terminal gif");
  // strcpy(commandsForGnuplot[1],"set output '| display gif:-'");  
  strcpy(commandsForGnuplot[0],"set xtics border out rotate by 90 offset character 0, -2, 0 autojustify");
  strcpy(commandsForGnuplot[1],"set xtics font ',5'");
  strcpy(commandsForGnuplot[2],"set ytics font ',6'");
  strcpy(commandsForGnuplot[3],"set ylabel 'Total number of Cases");
  strcpy(commandsForGnuplot[4],"set xlabel 'Date'");
  strcpy(commandsForGnuplot[5],"set grid");
  strcpy(commandsForGnuplot[6],"unset key");
  if (view == 2) {    
    strcpy(commandsForGnuplot[7],"plot for [i=2:2] 'data.temp' every 2 using i:xtic(1) lc 'red' lw 1.5 smooth acsplines");
  } else {
    strcpy(commandsForGnuplot[7],"plot for [i=2:2] 'data.temp' every 2 using i:xtic(1) lc 'blue' lw 1.5 smooth mcsplines");
  }
  /* If need to plot using every 3rd x value, can use every 3 as follows  
     strcpy(commandsForGnuplot[7],"plot for [i=2:2] 'data.temp' every 3 using i:xtic(1) lc 'blue' lw 1.5 smooth mcsplines"); 
     So to plot the 3rd column vs. the 1st, and plot every 3rd row starting from the 2nd, I do plot "filename" every 3::1 using 1:3 */
  
 //  strcpy(commandsForGnuplot[7],"plot for [i=2:2] 'data.temp' using i:xtic(1) lw 1.5 smooth mcsplines");
 //  "plot for [i=2:2] 'data.temp' using i:xtic(1) lw 1.5 smooth acsplines"};
  
  char * commandForGnuplotOne[] = 
    {"set xtics border out rotate by 90 offset character 0, -2, 0 autojustify",
     "set xtics font ',5'",
     "set ytics font ',6'",
     "set ylabel 'Total number of Cases",
     "set xlabel 'Date'",
     "set grid",
     "unset key",
     "plot for [i=2:2] 'data.temp' using i:xtic(1)"};
   
  FILE *temp = fopen("data.temp", "w");   /* LINUX PATH */
 // FILE *temp = fopen("C:\\Users\\gsignorini\\Documents\\pandemic\\data.temp", "w"); //WINDOWS

  /* The option -persistent will leave gnuplot running even when application is closed.
     Noted that gnuplot-qt session for each graph and this session remains even when graph
     is closed. Seems to cause gnuplot to crash after many graphs open. */

 // FILE * gnuplotPipe = popen("gnuplot -persistent 2> /dev/null", "w"); //LINUX
  
  FILE * gnuplotPipe = popen("gnuplot 2> /dev/null", "w"); //LINUX
    
 //  FILE * gnuplotPipe = popen("gnuplot -persistent", "w");   //windows
  /* 2> /dev/null (nul in windows) prevents gnuplot warning messages when range is auto adjusted, 
     these warnings make program exit */

  for (i=0; i < numrec; i++)
      fprintf(temp, "%d %d \n", arrayDate[i], arraytcases[i]); //Write the data to a temporary file
    
  if (numrec > 1) {
    if (choice == 2){
      fprintf(gnuplotPipe, "set title 'TOTAL CASES COVID 19 - %s'\n", countryname);
    } else if (choice == 3){
      fprintf(gnuplotPipe, "set title 'TOTAL DEATHS COVID 19 - %s'\n", countryname);
    } else if (choice == 5) {
      fprintf(gnuplotPipe, "set title 'NEW CASES COVID 19 - %s'\n", countryname);
    } else if (choice == 6) {
      fprintf(gnuplotPipe, "set title 'NEW DEATHS COVID 19 - %s'\n", countryname);
    }
    for (i=0; i < numOfCommands; i++) {
       fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
     }
  }

  if (numrec == 1) {
      if (choice == 2){
      fprintf(gnuplotPipe, "set title 'TOTAL CASES COVID 19 - %s'\n", countryname);
    } else if (choice == 3){
      fprintf(gnuplotPipe, "set title 'TOTAL DEATHS COVID 19 - %s'\n", countryname);
    } else if (choice == 5) {
      fprintf(gnuplotPipe, "set title 'NEW CASES COVID 19 - %s'\n", countryname);
    } else if (choice == 6) {
      fprintf(gnuplotPipe, "set title 'NEW DEATHS COVID 19 - %s'\n", countryname);
    }   
      for (i=0; i < numOfCommands; i++) {
        fprintf(gnuplotPipe, "%s \n", commandForGnuplotOne[i]); //Send commands to gnuplot one by one.
     }
   }
  /* Need both to allow graph to plot while terminal program remains in focus */
  fflush(temp);
  fflush(gnuplotPipe);
  fclose(temp);
  
  /*  could look at using gethar to hit enter so newline would close graph and go back to main menu 
  int cls =0;
  printf("CLOSE WINDOW");
  scanf("%d", &cls);
  if (cls == 1)
  pclose(gnuplotPipe); */

  /* another option (better option) to close graph before opening new one 

  while ((c = getchar()) != '1')
     printf("enter 1 to continue...");
    pclose(gnuplotPipe);
  */
}

/* Plot new total cases and new total deaths by country */
void countryGraphTotDC(int *arrayDate, int *arraytcases, int *arraydcases, int numrec, char countryname[]) {
  char filename[10];
  int i;
  int j;
  int *row;
  int numOfCommands = 12;   /*increase this if number of commands in commandsForGnuplot[] increases */
 
  char * commandsForGnuplot[]  =
    {"set xtics border out rotate by 90 offset character 0, -2, 0 autojustify",
     "set xtics font ',5'",
     "set ytics font ',6'",
     "set ylabel 'Total number of Cases'",
     "set ytics nomirror",
     "set y2tics",
     "set y2tics font ',6'",
     "set y2label 'Total number of Deaths",
     "set xlabel 'Date'",
     "set key font ',6'",
     "set grid",
     "plot 'data.temp' every 2 using 0:2:xtic(1) title 'cases' lw 1.5 with lines axes x1y1, 'data.temp' every 2 using 0:3:xtic(1) title 'deaths' lw 1.5 with lines axes x1y2"}; 
     //"unset key",
     //"plot for [i=2:3] 'data.temp' using i:xtic(1) lw 1.5 with lines"};
   char * commandForGnuplotOne[] = //{"plot 'data.temp'"};
    {"set xtics border out rotate by 90 offset character 0, -2, 0 autojustify",
     "set xtics font ',5'",
     "set ytics font ',6'",
     "set ylabel 'Total number of Cases",
     "set xlabel 'Date'",
     "set grid",
     "unset key",
     "plot for [i=2:3] 'data.temp' using i:xtic(1)"};
   
   FILE *temp = fopen("data.temp", "w");   // LINUX
 // FILE *temp = fopen("C:\\Users\\gsignorini\\Documents\\pandemic\\data.temp", "w");  //WINDOWS

 // FILE * gnuplotPipe = popen("gnuplot -persistent 2> /dev/null", "w");  /* LINUX */
    FILE * gnuplotPipe = popen("gnuplot 2> /dev/null", "w");  /* LINUX */
 // FILE * gnuplotPipe = popen("gnuplot -persistent", "w");  //WINDOWS
  /* 2> /dev/null (nul in windows) prevents gnuplot warning messages when range is auto adjusted, 
     these warnings make program exit */
  
  for (i=0; i < numrec; i++)
    fprintf(temp, "%d %d %d\n", arrayDate[i], arraytcases[i], arraydcases[i]); //Write the data to a temporary file
    

  if (numrec > 1) {
      fprintf(gnuplotPipe, "set title 'TOTAL CASES AND DEATHS COVID 19 - %s'\n", countryname);  // this allow me to have a variable title
    for (i=0; i < numOfCommands; i++) {
       fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
     }
  }

  if (numrec == 1) {
    	fprintf(gnuplotPipe, "set title 'COVID 19 - %s'\n", countryname);  // this allow me to have a variable title
      for (i=0; i < numOfCommands; i++) {
      fprintf(gnuplotPipe, "%s \n", commandForGnuplotOne[i]); //Send commands to gnuplot one by one.
     }
   }
  /* Need both to allow graph to plot while terminal program remains in focus */
  fflush(temp);
  fflush(gnuplotPipe);
  fclose(temp); 
}


/* Finds the most recent date uploaded, did consider using audit file */
int getDate(struct country *start) {
  struct country *ptr = start;
  int rdate = 0;
  while (ptr != NULL) {
    if (ptr->recdate > rdate){
      rdate = ptr->recdate;
    } else {
      ptr = ptr->next;
    }
  }
  printf("most recent date %d\n", rdate);
  return rdate;
}
   
int getDateRecNum(struct country *start, int rdate) {
  struct country *ptr = start;
  int c = 0;
  while (ptr != NULL) {
    if (ptr->recdate == rdate) {
	ptr = ptr->next;
	c++;
      } else {
	ptr = ptr->next;
      }
      }
  printf("number of records with date %d\n", c);
						  
  return c;
}

char **getDateRecCountry(struct country *start, int rdate, int rdatenum) {
  struct country *ptr = start;
  char **ctryName;
  int i = 0;
  ctryName = malloc(rdatenum*sizeof(char*));
  while (ptr != NULL){
    if(ptr->recdate == rdate){
      ctryName[i] = malloc(coName*sizeof(char));
      strcpy(ctryName[i], ptr->nation);
      ptr = ptr->next;
      i++;
    }else {
    ptr = ptr->next;
    }
  }
  return ctryName;
}


int * getDateRecCountryCases(struct country *start, char **ctryName, int rdate, int rdatenum, int ptype){
  struct country *ptr = start;
  int *icases;
  int i = 0;

  printf("DATE %d\n", rdate);
  icases = malloc(rdatenum*sizeof(int));
  
  while (ptr != NULL) {
    for (i=0; i<rdatenum; i++){
      if((strcmp(ctryName[i], ptr->nation) == 0) && rdate == ptr->recdate) {
	if (ptype == 1){
 	  icases[i] = ptr->tcases;
	} else if (ptype == 2){
	  icases[i] = ptr->tdeaths;
	} else {
	  icases[i] = ptr->tcases;
	}
     }
    }
    ptr = ptr->next;
  }
  return icases;
}
    

  
      
