#ifndef _APIGET_H
#define _APIGET_H

#define APICOUNTRY 35
#define UPLDFILE 8

struct apiGetData {
  char apiCountryName[APICOUNTRY];
  char apiCountryCode[3];
  int apiNewConfirmed;
  int apiTotalConfirmed;
  int apiNewDeathsConfirmed;
  int apiTotalDeaths;
  char apiUploadDate[21];
  int apiRequiredDate;
  struct apiGetData *next;
};
  typedef struct apiGetData apiGetData;

struct apiAlias {
  char apiCoName[APICOUNTRY];
  char apiCoAlias[3];
  struct apiAlias *next;
};
  typedef struct apiAlias apiAlias;


struct apiGetData *apiCreateCountry(char *, char *, int, int, int, int, char *, int);
struct apiGetData *apiAppend(struct apiGetData *, struct apiGetData *);
void apiPrintCountry(struct apiGetData *);
void apiFreeCountry(struct apiGetData *);
char **apiDataDate(struct apiGetData *);
int formatDate(char **);
void apiPrintCountryFinal(struct apiGetData *);
void apiCorrectDate(struct apiGetData *, int);

struct apiAlias *apiCreateAliasList(char *, char *);
struct apiAlias *apiAliasAppend(struct apiAlias *, struct apiAlias *);
void apiPrintAlias(struct apiAlias *);
void apiFreeAlias(struct apiAlias *);
void apiCorrectCountryName(struct apiGetData *, struct apiAlias *, int);

void makeUploadFile(struct apiGetData *, int);

#endif


