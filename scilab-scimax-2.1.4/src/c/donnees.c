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

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "stack-c.h"
#include "maxsci1.h"
#include "maxsci.h"

int creerSym (int, char *, char **, int, int, char);
inline int* creerSym2 (int, int);
int recupResult (int);
void envoiDonnees (void);
int detecteErreurs (void);
void gererQuestion (void);

void * G_tabptr[MAXVARS];

const static int taba2s[128] = 
{ 100,101,102,103,104,105,106,107,108,-40,
  110,111,112,113,114,115,116,117,118,119,
 120,121,122,123,124,125,126,127,128,129,
 130,131, 40, 38,-53, 37, 39, 56, 58, 53,
  41, 42, 47, 45, 52, 46, 51, 48,  0,  1,
   2,  3,  4,  5,  6,  7,  8,  9, 44, 43,
  59, 50, 60,-38,-61,-10,-11,-12,-13,-14,
 -15,-16,-17,-18,-19,-20,-21,-22,-23,-24,
 -25,-26,-27,-28,-29,-30,-31,-32,-33,-34,
 -35, 54, 49, 55, 62, 36,-59, 10, 11, 12,
  13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
  23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
  33, 34, 35,-54, 57,-55, 61, 127};

const static int tabSym[35] =
 { 17,3,1,9,13,18,10,3,1,0,1,
   4,5,8,28,34,22,29,27,14,25,
   0,10,1,1,0,1,2,-22,4,10,1,1,0,1};
 
extern void maxkill (void);

int
creerSym (pos, stro, tabstro, m, n, type)
     int pos, m, n;
     char *stro, **tabstro, type;
{
  static int lr;
  char *tp = &type;

  CreateVar (pos, "m", &trois, &un, &lr);
  CreateListVarFromPtr (pos, 1, SMD, &trois, &un, tabS);
  CreateListVarFromPtr (pos, 2, SD, &un, &un, &tp);
  if (tabstro == NULL)
    {
      CreateListVarFromPtr (pos, 3, SD, &m, &n, &stro);
    }
  else
    {
      CreateListVarFromPtr (pos, 3, SMD, &m, &n, tabstro);
    }
  
  return 0;
}

inline int*
creerSym2 (pos,taille)
     int pos, taille;
{
  int i;
  int *header;

  C2F(createdata) (&pos, sizeof (int) * (taille + 34));
  header = (int*)stk (*Lstk (pos + Top - Rhs));
  for (i = 0; i < 35; i++)
    header[i] = tabSym[i];
  return header;
}

int
recupResult (pos)
     int pos;
{
  unsigned char tp, c;
  int len ,total, mn, mn2, *header, *headers;
  char *str;
  register int k;

  k = detecteErreurs ();
  if (k == -1 || k == 1)
    return k;

  tp = buf[4];
  
  VIDEOS; total = atoi (buf);
  //Si la chaine de retour est vide, on sort
  if (total == 3)
    {
      VIDEOS;
      VIDEOS;
      return 1;
    }  
  headers = creerSym2 (pos, total);
  header = headers + 31;
  if (tp == 'E')
    {    
      header[4] = total - 2;
      mn = 2;
      mn2 = 4;
      tp = 'M';
    }
  else
    {
      VIDEOS; header[0] = atoi (buf);
      VIDEOS; header[1] = atoi (buf);
      mn = header[0] * header[1] + 1;
      mn2 = mn + 2;
      for (k = 3; k < mn2 + 1;header[k++] = (VIDEOS, atoi (buf)));
    }
  len = header[mn2] + mn2;
  for (k = mn2 + 1; k < len; k++)
    {
      c = Getc (os);
      header[k] = (c<127) ? taba2s[c] : c + 100;
    }
  
  headers[5] = 14 + (len>>1);
  headers[28] = taba2s[tp];
  
  // On vide ce qui reste sur l'outputstream
  for (k = 0; k < 6; k++) Getc (os);
  return 0;
}

void CANCEL (void)
{
  Putc ('$', is);
  Putc ('\n', is);
  fflush (is);
  do VIDEOS;
  while (!iseo (buf));
}

int detecteErreurs (void)
{
  char a, b, c, d, e;

  do VIDEOS;
  while (!isbo (buf) && (a=!isbe (buf)) && (b=!isbq (buf)) && (c=!isbs (buf)) && (d=!isbc (buf)) && !iseo (buf) && (e=!isbd (buf)));
  
  if (!a)
    {
      Scierror (9999, "Maxima error :\n");
      while ((VIDEOS, !isee (buf)))
	sciprint (buf);
      VIDEOS;
      return -1;
    }
  if (!b)
    {
      gererQuestion ();
      quest_mode = 1;
      return 1;
    }
  if (!c)
    {
      Scierror (9999, "A serious error occured\r\n");
      maxkill ();
      return -1;
    }
  if (!d)
    {
      sciprint ("Creating function in Maxima...\r\n");
      while ((VIDEOS, !isbo (buf)));
      return 0;
    }
  if (!e)
    {
      max_is_ok = 1;
      Scierror (9999, "\nMaxima started but it could not load scimax or scimath.\r\nGo to the directory src/lisp, read the README file and try to fix the problem.\r\nSend me an email to report the bug.\r\n\n");
      maxkill ();
      return -1;
    }
}

void gererQuestion (void)
{
  sciprint ("\n? Maxima Question\n");
  sciprint ("   * To answer use the function answer('your answer')\n");
  sciprint ("   * If you don't want to answer use the function noanswer\n\n");
  while ((VIDEOS, !iseq (buf)))
    sciprint("%s", buf);
}
