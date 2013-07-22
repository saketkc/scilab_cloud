//    <SciMax, a Scilab toolbox to connect Maxima.>
//    Copyright (C) <2009>  <Calixte DENIZET>

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.

//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.


//   Contact : Calixte DENIZET <calixte.denizet@ac-rennes.fr>

#include <stdio.h>
#include <string.h>

//#define DBG 1
#ifdef DBG
#define VIDEOS (fgets(buf,BUFSIZE,os),fprintf(stdout,"%s",buf))
#else
#define VIDEOS fgets(buf,BUFSIZE,os)
#endif

#define isbd(ch) (*((int*)ch)==*((int*)"<BD>"))
#define isbo(ch) (*((int*)ch)==*((int*)"<BO>"))
#define iseo(ch) (*((int*)ch)==*((int*)"<EO>"))
#define isbe(ch) (*((int*)ch)==*((int*)"<BE>"))
#define isee(ch) (*((int*)ch)==*((int*)"<EE>"))
#define isbs(ch) (*((int*)ch)==*((int*)"<BS>"))
#define isbc(ch) (*((int*)ch)==*((int*)"<BC>"))
#define isbq(ch) (*((int*)ch)==*((int*)"<BQ>"))
#define iseq(ch) (*((int*)ch)==*((int*)"<EQ>"))
#define Putc(_ch,_fp) putc_unlocked(_ch,_fp)
#define Getc(_fp) getc_unlocked(_fp)

#define BUFSIZE 256

#ifdef GLOBAL
unsigned char max_is_ok=0;
pid_t pid;
FILE *is,*os;
char buf[BUFSIZE];
unsigned char quest_mode=0;
#else
extern unsigned char max_is_ok;
extern pid_t pid;
extern FILE *is,*os,*ds;
extern char buf[BUFSIZE];
extern unsigned char quest_mode;
#endif

#define SD "c"
#define SMD "S"
#define L "l"
#define ML "M"

static int zero=0,un=1,deux=2,trois=3,quatre=4,cinq=5;
const static char* tabS[3]={"sym","t","rep"};
const static char* M = "M";
