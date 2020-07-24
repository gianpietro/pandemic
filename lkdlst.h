#ifndef _LKDLST_H
#define _LKDLST_H

#define COUNTRY 25   /* if value changed see also coName in lkdlst.c */
#define UPLOAD 15    /* data file to be uploaded */

 struct country {
  char nation[COUNTRY];
  int recdate; 
  int tcases;
  int tdeaths;
   int dcases;
   int ddeaths;
  struct country *next;
};
    typedef struct country country;

/* functions to create, search, print and free memory from linked list */
struct country *createCountry(char *, int,  int, int, int, int);
struct country *append(struct country *, struct country *);
void searchCountry(struct country *, char *);
void printCountry(struct country *);
void freeCountry(struct country *);

/* functions to obtain number of data records for a country */
int getCoRec(struct country *, char *);
int * getCoRecdate(struct country *, char *, int);

/* function to build array of cases for y value in graph */
int * filterCo(struct country *, char *, int *, int, int );
int * filterDCo(struct country *, char *, int *, int, int);

/* function to draw graph using gnuplot */
void countryGraph(int *, int *, int, char *, int, int);
void countryGraphTotDC(int *, int *, int *,int, char *);

/* functions to find infection percentage of population */
int getDate(struct country *);
int getDateRecNum(struct country *, int);
char **getDateRecCountry(struct country *, int, int);
int * getDateRecCountryCases(struct country *, char **,int, int, int);

#endif

  
