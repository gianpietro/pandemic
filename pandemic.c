/* Program to record information relating to coronavirus pandemic
for various countries. Information to store number of cases and 
plot a graph using gnuplot 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lkdlst.h"
#include "mltgrp.h"
#include "poplib.h"




int main(void) {
  struct country *start, *newCountryPtr, *end, *ptr;
  char name[COUNTRY];
  char s[COUNTRY];
  char c[COUNTRY];
  int totalcases, totaldeaths, dailycases, dailydeaths;
  int rcdate;
  int n, i = 0;
  int numrec = 0;  /* number of records in date array for country being searched */
  int *arrayDate;
  int m;
  int *arraytcases, *arraydcases;
  int choice = 0;
  int f=0, g, p=0;   /* option 7 */
  char **compare;
  FILE *fp;
  /* livedata upload variables */
  char filename[UPLOAD];
  char * extension = ".dat";
  struct country *ufstart, *ufnewCountryPtr, *ufend, *ufptr;
  char fileSpec[UPLOAD+strlen(extension)+1];
  FILE *temp;
  FILE *uf;
  FILE *ufp;
  char path[] = "livedata/";
  char ufname[UPLOAD];
  char **ufdata; 
  int ucount = 0;
  int z, u=0, auditcheck=0, v=0;
  /* popoulation variables */
  struct population *pstart, *pCountryPtr, *pend, *pptr;
  FILE *fpop;  
  char pname[CTNAME];
  int totalpop, pop = 0, poploaded = 0, idate, idatenum =0, ic;
  char **icountryArray;
  int *icasesArray;
  double *iperPopArray;
  /* graph view variables */
  int gview = 1;
  /* population infection rate range */
  int is = 0, ptype =0, gsort = 0;
  double rg = 00.0000, rl = 00.0000;
  
  
  fp = fopen("datafile.dat", "r");

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
    printf("********************************************************************\n");
    printf("************** P A N D E M I C -  C O V I D 19 *********************\n");
    printf("****************** Graph plots of world cases **********************\n");
    printf("********************************************************************\n");
    printf("Option 1:  Display list of all data\n\n");
    printf("Option 2:  Graph - Total Cases by Country\n\n");
    printf("option 3:  Graph - Total Deaths by Country\n\n");
    printf("Option 4:  Graph - Total Cases and Deaths by Country\n\n");
    printf("Option 5:  Graph - New Cases by Country\n\n");
    printf("Option 6:  Graph - New Deaths by Country\n\n");
    printf("Option 7:  Graph - Campare New Cases by Countries\n\n");
    printf("Option 8:  Upload data files\n\n");
    printf("Option 10: Percentage of Population Infected\n\n");
    printf("Option 11: Select Graph View Type\n\n");
    printf("Option 99: Exit\n\n");
    printf("\n");
    printf("Select option: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        /* print struct content of linked list */ 
        printCountry(start);
      break;
      case 2:
        printf("GVIEW %d\n", gview);
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
        countryGraph(arrayDate, arraytcases, numrec, s, choice, gview);     
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
	countryGraph(arrayDate, arraydcases, numrec, s, choice, gview);
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
        countryGraph(arrayDate, arraytcases, numrec, s, choice, gview);     
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
	countryGraph(arrayDate, arraydcases, numrec, s, choice, gview);
        free(arraydcases);
        free(arrayDate); 
      break;
      case 7:
        printf("Number of countries to compare (max is 5): ");
        scanf("%d", &f);
        if (f <= 5){
	  compare = malloc(f*sizeof(char*));      /* malloc for number of countries to compare */
          for (g=0; g<f; g++){
            printf("Enter country ");
	    scanf("%s", s);	
	    compare[g] = malloc(COUNTRY*sizeof(char));    /* malloc for char length of country name */
	    strcpy(compare[g], s);
	    printf("compare %s\n", compare[g]);
	  } 
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
	  buildGraph(g, gview);
	  free(compare);	
        }
      break;
      case 8:
        ucount = 0;
        strcpy(path,"livedata/");
        auditcheck = 0;
        printf("value of u 1st %d\n", u);
        u = 0;
      
      /* code to count number of items in audit file and load filename into array */
        uf = fopen("auditfile.dat", "r");
        if (uf == NULL){
  	  printf("No File exists ");
          break; 
	}
       
        while (fscanf(uf, "%s", ufname) != EOF) {
          ++ucount;
        }
       
        fclose(uf);
       
        printf("ucount first scan %d\n", ucount);
       
        ufdata = malloc(ucount * sizeof(char*));
       
        uf = fopen("auditfile.dat", "r");
        ucount = 0;
       
        while (fscanf(uf, "%s", ufname) != EOF) {
	  ufdata[ucount] = malloc(UPLOAD * sizeof(char));
	  strcpy(ufdata[ucount], ufname);
	  printf("ucount %d\n", ucount);
	  ++ucount;
        }
       
        fclose(uf);
       
        printf("ucount second scan %d\n", ucount);
        for (z=0; z<ucount; z++)
          printf("upload filename %s\n",ufdata[z]);

        /* code to enter filename to import  */
        printf("Enter filename to import ");
        scanf("%s", filename);
        snprintf(fileSpec, sizeof(fileSpec), "%s%s", filename, extension);
        printf("FILENAME %s\n", fileSpec);   //debug code
        strcat(path, fileSpec);
        printf("path %s\n", path);        
      
       /* check to see if file entered to be uploaded is in auditfile */
        for (z=0; z<ucount; z++){
	  if (strcmp(ufdata[z], fileSpec) == 0) {
	    printf("File is in auditfile\n");
	    auditcheck = 1;
	  }
        }

       /* If file to upload is not found in auditfile then it can be uploaded */
        if (auditcheck == 0) {
          temp = fopen(path, "r");
          if (temp == NULL) {
            fprintf(stdout, "ERROR file not found\n");
            break;
          }

	  printf("value of u 2nd %d\n", u);
       /* if file is not in auditfile load to country structure */
        while (fscanf(temp, "%s %d %d %d %d %d", name, &rcdate, &totalcases, &totaldeaths, &dailycases, &dailydeaths) != EOF) {   
          if (u == 0) {
            ufstart = createCountry(name, rcdate, totalcases, totaldeaths, dailycases, dailydeaths);
            ufend = ufstart;
          } else {
            ufnewCountryPtr = createCountry(name, rcdate, totalcases, totaldeaths, dailycases, dailydeaths);
            ufend = append(ufend, ufnewCountryPtr);
          }       
          u++;
	  printf("value of u 3rd %d\n", u);
         }

	printf("value of u 4th %d\n", u);
	 
        fclose(temp);
       
        printCountry(ufstart);
       
        /* add uploaded filename to the auditfile */
        uf = fopen("auditfile.dat", "a");
        fprintf(uf, "%s\n", fileSpec);
        fclose(uf);
       
        /* write data from uploaded file to the main datafile */
        ufp = fopen("datafile.dat", "a");
        if (ufp == NULL) {
          fprintf(stdout,"\nError opening file\n");
          break;
        }
        ufptr = ufstart;
       
        while(ufptr != NULL)
        {
          fprintf(ufp, "%s %d %d %d %d %d\n", ufptr->nation, ufptr->recdate, ufptr->tcases, ufptr->tdeaths, ufptr->dcases, ufptr->ddeaths);
	  ufptr = ufptr->next;
        }

        fclose(ufp);

        freeCountry(ufstart);
      }
	
       /* free memory from ufdata array */
        for (z=0; z<ucount; z++)
          free(ufdata[z]);
        free(ufdata);
      break;
      case 10:
        if (poploaded == 0) {
          fpop = fopen("datapopfile.dat", "r");
	  if (fpop == NULL) {
            fprintf(stdout,"\nError opening file\n");
            exit(1);
          }
          while (fscanf(fpop, "%s %d", pname, &totalpop) != EOF) {
            if (pop == 0) {
              pstart = popCreateCountry(pname, totalpop);
              pend = pstart;
            } else {
              pCountryPtr = popCreateCountry(pname, totalpop);
              pend = popAppend(pend, pCountryPtr);
            }       
          pop++;
        }
          fclose(fpop);
          poploaded = 1;
        } else {
	    printf("Population already loaded \n");
        }
        popPrintCountry(pstart);	
	/* optain most recent date in datafile */
	idate = getDate(start);
	/* count number of records which have idate */	
	idatenum = getDateRecNum(start, idate);
	/* array of countries with idate */
	icountryArray = getDateRecCountry(start, idate, idatenum);
	/*for (i=0;i<idatenum;i++){
	  printf("country in array %s\n", icountryArray[i]);
	  }*/
        printf("\nSelect one of the following options:\n");
	printf("Enter 1 - percentage based on total cases\n");
	printf("Enter 2 - percentage based on total deaths\n");
	printf("Enter option: ");
        scanf("%d", &ptype);
	printf("Sort high to low options  Yes = 1, No = 2:  ");
	scanf("%d", &gsort);
	
	
        /* array of total cases for country on idate */ 
	icasesArray = getDateRecCountryCases(start, icountryArray, idate, idatenum, ptype);	
        /* array of percentage of population infected */
        iperPopArray = infectionPercent(pstart, icountryArray, icasesArray, idatenum);

	//printf("For percentage equale to or greater than (enter %): ");
	//scanf("%lf", &irateGr);
	if(gsort == 1)
	  printPercInfection(pstart,icountryArray,iperPopArray,idatenum);
	 
       printf("\nSelect one of the following:\n");
       printf("1 - Rate equale to or greater than.\n");
       printf("2 - Range between two rates.\n");
       printf("3 - Rate equale to or less than.\n");
       printf("4 - All data all countries\n");
       printf("Select option required: ");
       scanf("%d",&is);
       if (is == 1){
          printf("Enter percentage greater of equale to: ");
	  scanf("%lf", &rg);
       } else if (is == 2) {
           printf("Enter percentage from: ");
	   scanf("%lf", &rg);
	   printf("Enter percentage to: ");
	   scanf("%lf", &rl);
       } else if (is == 3){
           printf("Enter percentage less or euqale to:");
	   scanf("%lf", &rl);
       } else if (is == 4){
	   rg = 00.0000;
       }
  
	/* prepare file with data */
       infectionGraph(icountryArray,iperPopArray, idatenum, is, rg, rl);

       if (gsort == 2)
         printPercInfection(pstart,icountryArray,iperPopArray,idatenum);
       
        /* plot graph */
	buildInfecGraph(ptype);
	/* free array memory */
	for (ic=0; ic<idatenum;ic++){
	  free(icountryArray[ic]);
	}
	free(icountryArray);
	free(icasesArray);
	free(iperPopArray);
      break;
      case 11:
	printf("Following graph plot views are available\n");
	printf("Enter 1 for default view\n");
	printf("Enter 2 for trend line plot view\n");
   	printf("Which view would you like to see: ");
	scanf("%d",&gview);	  
	printf("view %d\n", gview);
      break;
      case 99:
        freeCountry(start);
        exit(0);
      break;
      }
    } while (choice != 99);

  return 0;
}


  
  
  



	  
       

      
