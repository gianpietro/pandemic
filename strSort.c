#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
 
  char temp[10];
  int i, j, p;
  int row = 5;   //number of items
  int col = 10;  //permitted length of each string

  /* implement country array and assign malloc */
  char **country;
  country = malloc(row*sizeof(char*));
  for (p=0; p<row; p++){
    country[p] = malloc(col*sizeof(char));
				 }
  strcpy(country[0], "usa");
  strcpy(country[1], "spain");
  strcpy(country[2], "italy");
  strcpy(country[3], "uk");
  strcpy(country[4], "germany");

  for (p=0; p<row; p++){
    printf("country %s\n", country[p]);
    }


  /* sort array into alphabetical order */
  for (i=0; i<row-1; i++)
    {
    for (j = i+1; j<row; j++)
      {
      if (strcmp(country[i], country[j]) > 0)
      {
        strcpy(temp, country[i]);
        strcpy(country[i], country[j]);
        strcpy(country[j], temp);
      }
   }      
  }
  
  printf("\nAlphabetical order\n");
  printf("---------------------\n");
  for (i=0; i<row; i++){
    printf("country %s\n",country[i]);
  }

  /* free malloc for array country */
  for (p=0; p<row; p++){
    free(country[p]);
  }
  free(country);
    
  return 0;
}
