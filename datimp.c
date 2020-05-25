#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datimp.h"

void uploadDataFiles(char filename[]) {
  char * a = filename;
  char * extension = ".dat";
  char fileSpec[strlen(a)+strlen(extension)+1];
  FILE *temp;
  char path[] = "livedata/";
  
  
  snprintf(fileSpec, sizeof(fileSpec), "%s%s", a, extension);
 
  printf("FILENAME %s\n", fileSpec);   //debug
  
  strcat(path, fileSpec);
   
  temp = fopen(path, "r");
  if (temp == NULL) {
    fprintf(stdout, "ERROR file not found\n");
    //exit(1);
  }

  

}
