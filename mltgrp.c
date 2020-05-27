#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mltgrp.h"


void compareGraph(int *arrayDate, int *arraytcases, int numrec, char countryname[], int g) {
  int i;
  char * a = "country";
  int b = g+1;
  char * extension = ".gp";
  char fileSpec[strlen(a)+b+strlen(extension)+1];

  FILE *temp;

  snprintf( fileSpec, sizeof( fileSpec ), "%s%d%s", a, b, extension );
  temp = fopen(fileSpec, "w");
  fprintf(temp, "%s\n", countryname);
  fclose(temp);
  temp = fopen(fileSpec, "a");
  
  for (i=0; i < numrec; i++)
    {
      fprintf(temp, "%d %d\n", arrayDate[i], arraytcases[i]); //Write the data to a temporary file
    }
  
  fflush(temp);
  fclose(temp);
}

void buildGraph(int g) {
   int numOfCommands = 8;   /*increase this if number of commands in commandsForGnuplot[] increases */
   int i;
   char commandsForGnuplot[8][200];

   printf("value of g %d\n", g);
   strcpy(commandsForGnuplot[0],"set xtics border out rotate by 90 offset character 0, -2, 0 autojustify");
   strcpy(commandsForGnuplot[1],"set xtics font ',5'");
   strcpy(commandsForGnuplot[2],"set ytics font ',6'");   
   strcpy(commandsForGnuplot[3],"set ylabel 'Number of New Cases");
   strcpy(commandsForGnuplot[4],"set xlabel 'Date'");
   strcpy(commandsForGnuplot[5],"set grid");
   strcpy(commandsForGnuplot[6],"set key autotitle columnhead");     
   if (g == 2){
   strcpy(commandsForGnuplot[7],"plot for [i=1:2] 'country'.i.'.gp' using 1:2:xtic(1) with lines");
   } else if ( g == 3){
   strcpy(commandsForGnuplot[7],"plot for [i=1:3] 'country'.i.'.gp' using 1:2:xtic(1) with lines");
   } else if ( g == 4){
   strcpy(commandsForGnuplot[7],"plot for [i=1:4] 'country'.i.'.gp' using 1:2:xtic(1) with lines");
   } else if ( g == 5){
   strcpy(commandsForGnuplot[7],"plot for [i=1:5] 'country'.i.'.gp' using 1:2:xtic(1) with lines");
   }

  FILE * gnuplotPipe = popen("gnuplot -persistent 2> /dev/null", "w"); 

  fprintf(gnuplotPipe, "set title 'NEW CASES' \n");
  
  for (i=0; i < numOfCommands; i++) {
       fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
     }

  fflush(gnuplotPipe);
}
