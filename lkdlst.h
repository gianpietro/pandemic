#ifndef _LKDLST_H
#define _LKDLST_H

#define COUNTRY 25

//extern int coName = 25;

 struct country {
  char nation[COUNTRY];
  int tcases;
  int tdeaths;
  int recdate;
  struct country *next;
};
    typedef struct country country;
//char countryname[COUNTRY];
//struct country *createCountry(char *,int, int, int);
//struct country *createCountry(char countryname[], int rcdate,  int totcases, int totdeaths);
struct country *createCountry(char *, int,  int, int);
  
#endif

  
