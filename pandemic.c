/*  (c) Gianpietro Signorini
Program to record information relating to coronavirus pandemic
for various countries. Information to store number of cases and 
plot a graph using gnuplot 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lkdlst.h"
#include "mltgrp.h"
#include "poplib.h"
#include "cJSON.h"
#include "apiget.h"


int main(void) {
  struct country *start, *newCountryPtr, *end, *ptr;
  char name[COUNTRY];
  char s[COUNTRY];
  char c[COUNTRY];
  int totalcases, totaldeaths, dailycases, dailydeaths;
  int rcdate;
  int n, i = 0;
  int numrec = 0;                                                        /* number of records in date array for country being searched */
  int *arrayDate;
  int m;
  int *arraytcases, *arraydcases;
  int choice = 0;
  int f=0, g, p=0;                                                       /* option 7 */
  char **compare;
  FILE *fp;
  /* livedata upload variables */
  char filename[UPLOAD];
  char *extension = ".dat";
  struct country *ufstart, *ufnewCountryPtr, *ufend, *ufptr;
  char fileSpec[UPLOAD+strlen(extension)+1];
  FILE *temp;
  FILE *uf;
  FILE *ufp;
  char path[] = "livedata/";
  char ufname[UPLOAD];
  char **ufdata; 
  int  ucount = 0;
  int  z, u=0, auditcheck=0, v=0;
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
  /* API link */
  FILE *api, *fapi;
  char apiStr[50000];
  struct apiGetData *apiStart, *apiNewCountryPtr, *apiEnd, *apiPtr;
  int apiList = 0;
  char **aliasName;
  struct apiAlias *aStart, *aNewAliasPtr, *aEnd, *aPtr;
  FILE *fAlias;
  char nameStr[COUNTRY];
  char aliasStr[3];
  int acount = 0;
  char **apiDateStr;
  int fileUploadDate;

    
  fp = fopen("datafile.dat", "r");

  if (fp == NULL) {
    fprintf(stdout,"\nError opening file\n");
    perror("Error "); 
  } 
  
  while (fscanf(fp, "%s %d %d %d %d %d", name, &rcdate, &totalcases, &totaldeaths, &dailycases, &dailydeaths) != EOF) {
    if (i == 0) {
      start = createCountry(name, rcdate, totalcases, totaldeaths, dailycases, dailydeaths);
      end = start;
    }
    else {
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
    printf("Option 12: API Covid data - make upload file\n\n");
    printf("Option 99: Exit\n\n");
    printf("\n");
    printf("Select option: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        /* Print struct content of linked list */ 
        printCountry(start);
        break;
      case 2:
        printf("Graph View %d\n", gview);
        /* Search for a particular country and print the values in its struct */
        printf("Search for a country: ");
        scanf("%s", s);
        searchCountry(start,s);
        /* Pulls back the number of records for the country searched */
        numrec = getCoRec(start,s);                           
        printf("number of record %d\n", numrec);

        /* Builds an array of the dates found for the country searched, 
           this will be number of data rows.
           The dates will have been sorted in ascending order */  
        arrayDate = getCoRecdate(start,s,numrec); 
        arraytcases =  filterCo(start, s, arrayDate, numrec, choice);
        countryGraph(arrayDate, arraytcases, numrec, s, choice, gview);
	
        free(arraytcases);
        free(arrayDate);
        break;
      case 3:
        printf("Search for a country: ");
        scanf("%s", s);
        searchCountry(start,s);
        /* Pulls back the number of records for the country searched */
        numrec = getCoRec(start,s);                           
        printf("number of record %d\n", numrec);

        /* Builds an array of the dates found for the country searched, 
           this will be number of data rows 
           The dates will have been sorted in ascending order */  
        arrayDate = getCoRecdate(start,s,numrec);
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
	printf("number of record %d\n", numrec);

	arrayDate = getCoRecdate(start,s,numrec);
        arraytcases =  filterCo(start, s, arrayDate, numrec, choice);
	arraydcases =  filterDCo(start, s, arrayDate, numrec, choice);
	countryGraphTotDC(arrayDate, arraytcases, arraydcases, numrec, s);
	
	free(arraytcases);
	free(arraydcases);
        free(arrayDate); 
        break;
      case 5:
        /* Search for a particular country and print the values in its struct */
        printf("Search for a country: ");
        scanf("%s", s);
        searchCountry(start,s);
        /* Pulls back the number of records for the country searched */
        numrec = getCoRec(start,s);                           
        printf("number of record %d\n", numrec);

        /* Builds an array of the dates found for the country searched, 
           this will be number of data rows. 
           The dates will have been sorted in ascending order */  
        arrayDate = getCoRecdate(start,s,numrec);
        arraytcases =  filterCo(start, s, arrayDate, numrec, choice);
        countryGraph(arrayDate, arraytcases, numrec, s, choice, gview);
	
        free(arraytcases);
        free(arrayDate);  
        break;
      case 6:
        printf("Search for a country: ");
        scanf("%s", s);
        searchCountry(start,s);
        /* Pulls back the number of records for thecountry searched */
        numrec = getCoRec(start,s);                           
        printf("number of record %d\n", numrec);

        /* Builds an array of the dates found for the country searched, 
           this will be number of data rows. 
           The dates will have been sorted in ascending order */  
        arrayDate = getCoRecdate(start,s,numrec);
	arraydcases =  filterDCo(start, s, arrayDate, numrec, choice);
	countryGraph(arrayDate, arraydcases, numrec, s, choice, gview);
	
        free(arraydcases);
        free(arrayDate); 
        break;
      case 7:
        printf("Number of countries to compare (max is 5): ");
        scanf("%d", &f);
        if (f <= 5){
	  compare = malloc(f*sizeof(char*));              /* malloc for number of countries to compare */
          for (g=0; g<f; g++){
            printf("Enter country ");
	    scanf("%s", s);	
	    compare[g] = malloc(COUNTRY*sizeof(char));    /* malloc for char length of country name */
	    strcpy(compare[g], s);
	    printf("compare %s\n", compare[g]);
	  } 
	  for (g=0; g<f; g++){
	    strcpy(s, compare[g]);
	    numrec = getCoRec(start, s);
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
        //printf("value of u 1st %d\n", u);
        u = 0;
      
        /* Count number of items in audit file and load filename into array */
        uf = fopen("auditfile.dat", "r");
        if (uf == NULL){
  	  printf("No File exists ");
          perror("Error "); 
	}
       
        while (fscanf(uf, "%s", ufname) != EOF) {
          ++ucount;
        }
       
        fclose(uf);
       
        //printf("ucount first scan %d\n", ucount);
       
        ufdata = malloc(ucount * sizeof(char*));
       
        uf = fopen("auditfile.dat", "r");
        ucount = 0;
       
        while (fscanf(uf, "%s", ufname) != EOF) {
	  ufdata[ucount] = malloc(UPLOAD * sizeof(char));
	  strcpy(ufdata[ucount], ufname);
	  ++ucount;
        }
       
        fclose(uf);
       
        for (z=0; z<ucount; z++)
          printf("upload filename %s\n",ufdata[z]);

        printf("Enter filename to import ");
        scanf("%s", filename);
        snprintf(fileSpec, sizeof(fileSpec), "%s%s", filename, extension);
        strcat(path, fileSpec);
        printf("path %s\n", path);        
      
        /* Check to see if file entered to be uploaded is in auditfile */
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

          /* If file is not in auditfile load data to country structure */
          while (fscanf(temp, "%s %d %d %d %d %d", name, &rcdate, &totalcases, &totaldeaths, &dailycases, &dailydeaths) != EOF) {   
            if (u == 0) {
              ufstart = createCountry(name, rcdate, totalcases, totaldeaths, dailycases, dailydeaths);
              ufend = ufstart;
	    }
	    else {
              ufnewCountryPtr = createCountry(name, rcdate, totalcases, totaldeaths, dailycases, dailydeaths);
              ufend = append(ufend, ufnewCountryPtr);
            }       
            u++;
         }

          fclose(temp);
       
          printCountry(ufstart);
       
          /* Add uploaded filename to the auditfile */
          uf = fopen("auditfile.dat", "a");
          fprintf(uf, "%s\n", fileSpec);
          fclose(uf);
       
          /* Write data from uploaded file to the main datafile */
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
	
        /* Free memory from ufdata array */
        for (z=0; z<ucount; z++)
          free(ufdata[z]);
        free(ufdata);	
        break;
      case 10:
        if (poploaded == 0) {
          fpop = fopen("datapopfile.dat", "r");
	  if (fpop == NULL) {
            fprintf(stdout,"\nError opening file\n");
            perror("Error ");
          }
          while (fscanf(fpop, "%s %d", pname, &totalpop) != EOF) {
            if (pop == 0) {
              pstart = popCreateCountry(pname, totalpop);
              pend = pstart;
            }
	    else {
              pCountryPtr = popCreateCountry(pname, totalpop);
              pend = popAppend(pend, pCountryPtr);
            }       
          pop++;
        }
          fclose(fpop);
          poploaded = 1;
        }
        else {
	    printf("Population already loaded \n");
        }
	
        popPrintCountry(pstart);	
	/* Optain most recent date in datafile */
	idate = getDate(start);
	/* Count number of records which have idate */	
	idatenum = getDateRecNum(start, idate);
	/* Array of countries with idate */
	icountryArray = getDateRecCountry(start, idate, idatenum);
	
        printf("\nSelect one of the following options:\n");
	printf("Enter 1 - percentage based on total cases\n");
	printf("Enter 2 - percentage based on total deaths\n");
	printf("Enter option: ");
        scanf("%d", &ptype);
	printf("Sort high to low options  Yes = 1, No = 2:  ");
	scanf("%d", &gsort);
		
        /* Array of total cases for country on idate */ 
	icasesArray = getDateRecCountryCases(start, icountryArray, idate, idatenum, ptype);	
        /* Array of percentage of population infected */
        iperPopArray = infectionPercent(pstart, icountryArray, icasesArray, idatenum);

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
        }
        else if (is == 2) {
          printf("Enter percentage from: ");
	  scanf("%lf", &rg);
	  printf("Enter percentage to: ");
	  scanf("%lf", &rl);
        }
        else if (is == 3){
          printf("Enter percentage less or euqale to:");
	  scanf("%lf", &rl);
        }
        else if (is == 4){
	  rg = 00.0000;
        }
  
        /* Prepare file with data */
        infectionGraph(icountryArray,iperPopArray, idatenum, is, rg, rl);

        if (gsort == 2)
          printPercInfection(pstart,icountryArray,iperPopArray,idatenum);
       
        /* Plot graph */
	buildInfecGraph(ptype);

	/* Free array memory */
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
      case 12:
        remove("summary");
	apiList = 0;
	acount = 0;
	int Countries_count = 0;

        /* Using application gwet to retrieve jason file from API */
        /* https://documenter.getpostman.com/view/10808728/SzS8rjbc?version=latest#e831c268-9da1-4d86-8b5a-8d7f61910af8 */
        //api = popen("wget -q https://api.covid19api.com/summary","w");
	api = popen("wget -cq --retry-connrefused --tries=5 --timeout=1 https://api.covid19api.com/summary", "w");
	fflush(api);
	pclose(api);
        fapi = fopen("summary", "r");

	if (fapi == NULL) {
	  perror("Error ");
          break; 
        }
	
        fread(apiStr, 50000, 1, fapi);  
        fclose(fapi);

        cJSON *root = cJSON_Parse(apiStr);

        const cJSON *Countries_Obj = cJSON_GetObjectItemCaseSensitive(root, "Countries");
       
        Countries_count = cJSON_GetArraySize(Countries_Obj);
        int idxData = 0;
	
        /*cJSON_ArrayForEach(Country_idx, Countries_Obj) {
          cJSON *Country_Obj = cJSON_GetObjectItemCaseSensitive(Country_idx, "Country");
	  cJSON *NewConfirmed_Obj = cJSON_GetObjectItemCaseSensitive(Country_idx, "NewConfirmed");
          cJSON *TotalConfirmed_Obj = cJSON_GetObjectItemCaseSensitive(Country_idx, "TotalConfirmed");
	  cJSON *NewDeaths_Obj = cJSON_GetObjectItemCaseSensitive(Country_idx, "NewDeaths");
	  cJSON *TotalDeaths_Obj = cJSON_GetObjectItemCaseSensitive(Country_idx, "TotalDeaths");
	  cJSON *Date_Obj = cJSON_GetObjectItemCaseSensitive(Country_idx, "Date");
          totCases = TotalConfirmed_Obj->valuedouble;
          printf("Country %s Total Confirmed %f Total Deaths %f New Confirmed %f New Deaths %f Date %s\n",
	       Country_Obj->valuestring, totCases, TotalDeaths_Obj->valuedouble, NewConfirmed_Obj->valuedouble, NewDeaths_Obj->valuedouble, Date_Obj->valuestring);
	 }*/

        for (idxData = 0; idxData < Countries_count; idxData++) {
          cJSON *CountryData_Array = cJSON_GetArrayItem(Countries_Obj, idxData);
          char *CountryName_Obj = cJSON_GetObjectItem(CountryData_Array, "Country")->valuestring;
	  char *CountryCode_Obj = cJSON_GetObjectItem(CountryData_Array, "CountryCode")->valuestring;
          int NewConfirmed_Obj = cJSON_GetObjectItem(CountryData_Array, "NewConfirmed")->valueint;
          int TotalConfirmed_Obj = cJSON_GetObjectItem(CountryData_Array, "TotalConfirmed")->valueint;
          int NewDeaths_Obj = cJSON_GetObjectItem(CountryData_Array, "NewDeaths")->valueint;
          int TotalDeaths_Obj = cJSON_GetObjectItem(CountryData_Array, "TotalDeaths")->valueint;
          char *Slug_Obj  = cJSON_GetObjectItem(CountryData_Array, "Slug")->valuestring;
          char *Date_Obj = cJSON_GetObjectItem(CountryData_Array, "Date")->valuestring;
	  int rd = 0;
       	  
	  if (apiList == 0) {
	    apiStart = apiCreateCountry(CountryName_Obj, CountryCode_Obj, NewConfirmed_Obj, TotalConfirmed_Obj, NewDeaths_Obj, TotalDeaths_Obj, Date_Obj, rd);
	    apiEnd = apiStart;
	  }
	  else {
	    apiNewCountryPtr = apiCreateCountry(CountryName_Obj, CountryCode_Obj, NewConfirmed_Obj,TotalConfirmed_Obj, NewDeaths_Obj, TotalDeaths_Obj, Date_Obj, rd);
	    apiEnd = apiAppend(apiEnd , apiNewCountryPtr);
	  }
	  apiList++;  	  
        }

        char *rendered = cJSON_Print(root);

	/* Convert string date to int date format */
	if (apiStart != NULL){
	  apiDateStr = apiDataDate(apiStart);
	  fileUploadDate = formatDate(apiDateStr);
	}

	apiCorrectDate(apiStart, fileUploadDate);
        
        /* Open datafile containing the country and its country code (alias)
           and pass data into linked list */
	fAlias = fopen("datacode.dat", "r");

        if(fAlias == NULL){
	  perror("Error");
          break;
        }

        while (fscanf(fAlias, "%s %s", nameStr, aliasStr) != EOF){
 	  if (acount == 0) {
	    aStart = apiCreateAliasList(nameStr, aliasStr);
	    aEnd = aStart;
	  }
	  else {
	    aNewAliasPtr = apiCreateAliasList(nameStr, aliasStr);
	    aEnd = apiAliasAppend(aEnd, aNewAliasPtr);
	  }
	  acount++;
        }

	apiCorrectCountryName(apiStart, aStart, acount);
	apiPrintCountry(apiStart);
	printf("File upload date %d\n",fileUploadDate);

	makeUploadFile(apiStart, fileUploadDate);

        free(rendered);	
        cJSON_Delete(root);
        break; 
      case 99:
        freeCountry(start);
	apiFreeCountry(apiStart);
	apiFreeAlias(aStart);
        exit(0);
        break;
      }
  } while (choice != 99);

  return 0;
}


  
  
  



	  
       

      
