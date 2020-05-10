#ifndef _LKDLST_H
#define _LKDLST_H

#define COUNTRY 25   /* if value changed see also coName in lkdlst.c */

 struct country {
  char nation[COUNTRY];
  int recdate; 
  int tcases;
  int tdeaths;
  struct country *next;
};
    typedef struct country country;

/* functions to create, search, preint and free memonotry for  linked list */
struct country *createCountry(char *, int,  int, int);
struct country *append(struct country *, struct country *);
void searchCountry(struct country *, char *);
void printCountry(struct country *);
void freeCountry(struct country *);

/* functions to obtain number of data records for a country */
int getCoRec(struct country *, char *);
int * getCoRecdate(struct country *, char *, int);

/* function to build array of cases for y value in graph */
int * filterCo(struct country *, char *, int *, int);

/* function to draw graph using gnuplot */
void countryGraph(int *, int *, int, char *);


#endif

  
