#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "args.h"
#include "mem.h"
#include "msg.h"
#include "strings.h"
#include "files.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint32_t ArgNumber(uint32_t d, char *a[], uint32_t n, char *s, uint32_t l,
uint32_t u){
  uint32_t x;
  for( ; --n ; ) if(!strcmp(s, a[n])){
    if((x = atol(a[n+1])) < l || x > u){
      fprintf(stderr, "[x] Invalid number! Interval: [%u;%u].\n", l, u);
      exit(EXIT_FAILURE);
      }
    return x;
    }
  return d;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

double ArgDouble(double def, char *arg[], uint32_t n, char *str){
  for( ; --n ; )
    if(!strcmp(str, arg[n]))
      return atof(arg[n+1]);
  return def;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint8_t ArgState(uint8_t def, char *arg[], uint32_t n, char *str){     
  for( ; --n ; )
    if(!strcmp(str, arg[n]))
      return def == 0 ? 1 : 0;
  return def;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

char *ArgString(char *def, char *arg[], uint32_t n, char *str){
  for( ; --n ; )
    if(!strcmp(str, arg[n]))
      return arg[n+1];
  return def;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint32_t ReadFNames(Parameters *P, char *arg){
  uint32_t nFiles = 1, k = 0, argLen;
  
  argLen = strlen(arg);
  for( ; k != argLen ; ++k)
    if(arg[k] == ':')
      ++nFiles;
  P->tar = (char **) Malloc(nFiles * sizeof(char *));
  P->tar[0] = strtok(arg, ":");
  TestReadFile(P->tar[0]);
  for(k = 1 ; k != nFiles ; ++k){
    P->tar[k] = strtok(NULL, ":");
    TestReadFile(P->tar[k]);
    }

  return nFiles;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void PrintArgs(Parameters *P){
  uint32_t n = 0;

  fprintf(stderr, "Verbose mode ....................... %s\n", !P->verbose ?
  "no" : "yes"); 
  fprintf(stderr, "Force mode ......................... %s\n", !P->force ? 
  "no" : "yes");
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -