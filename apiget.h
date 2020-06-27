#ifndef _APIGET_H
#define _APIGET_H

#define APICOUNTRY 35

struct apiGetData {
  char apiCountryName[APICOUNTRY];
  char apiCountryCode[3];
  int apiNewConfirmed;
  int apiTotalConfirmed;
  int apiNewDeathsConfirmed;
  int apiTotalDeaths;
  char apiUploadDate[21];
  struct apiGetData *next;
};
  typedef struct apiGetData apiGetData;

struct apiGetData *apiCreateCountry(char *, char *, int, int, int, int, char *);
struct apiGetData *apiAppend(struct apiGetData *, struct apiGetData *);
void apiPrintCountry(struct apiGetData *);
void apiFreeCountry(struct apiGetData *);
  


#endif


