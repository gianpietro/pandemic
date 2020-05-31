#ifndef _POPLIB_H
#define _POPLIB_H

#define CTNAME 25

struct population {
  char nation[CTNAME];
  int tpop;
  struct population  *next;
};

  typedef struct population population;

  struct population *popCreateCountry(char *, int);
  struct population *popAppend(struct population *, struct population *);
  void popPrintCountry(struct population *);

#endif
