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
	printf("country: %s pop %d cases: %d rate: %2.4f\n",icountryArray[i], ptr->tpop, icasesArray[i], perc[i]);
	ptr = ptr->next;
       } else {
        ptr = ptr->next;
      }
    }
    ptr = start;
  }
  return perc;
}

	  
void infectionGraph(char **icountryArray, double *iperpopArray, int idatenum, int is, double rg, double rl) {
  int i;

  FILE *temp;

  temp = fopen("datapop.temp", "w"); 
  
  for (i=0; i<idatenum; i++) {
    if (is == 1 || is == 4){
      if (iperpopArray[i] >= rg)
        fprintf(temp, "%s %2.4f\n", icountryArray[i], iperpopArray[i]);
    } else if (is == 2) {
      if (iperpopArray[i] >= rg && iperpopArray[i] <= rl)
	fprintf(temp, "%s %2.4f\n", icountryArray[i], iperpopArray[i]);
    } else if (is == 3){
      if (iperpopArray[i] <= rl)
	fprintf(temp, "%s %2.4f\n", icountryArray[i], iperpopArray[i]);
    }      
  }

  fflush(temp);
  fclose(temp);
}
		  
      
void buildInfecGraph() {
   int numOfCommands = 9;   /*increase this if number of commands in commandsForGnuplot[] increases */
   int i;

   char * commandsForGnuplot[]  =
    {"set xtics border out rotate by 90 offset character 0, -2, 0 autojustify",
     "set style data histograms",
     "set xtics font ',8'",
     "set ytics font ',6'",
     "set ylabel 'Percentage Infected",
     "set xlabel 'Country'",
     "set grid",
     "unset key",
     "plot for [i=2:2] 'datapop.temp' using i:xtic(1)"};


   FILE * gnuplotPipe = popen("gnuplot 2> /dev/null", "w"); 

   fprintf(gnuplotPipe, "set title 'Percentage of population who have been infected' \n");
  
  for (i=0; i < numOfCommands; i++) {
       fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
     }

  fflush(gnuplotPipe);
  
}


  
  


