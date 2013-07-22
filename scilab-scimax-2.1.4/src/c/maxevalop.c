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

#include "stack-c.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "maxsci1.h"
#include "maxsci.h"
#include "operateurs.h"

extern int gestionVar (int);
extern void envoiDonnees (void);
extern void CANCEL (void);
extern int recupResult (int);

inline void determineOp (char);

int
maxevalop (pos, stri)
     int pos;
     char *stri;
{
  int k, t, lr;

  G_nb.vars = 0;
  G_nb.appels = 0;
  
  Putc ('_', is);
  Putc ('(', is);
  
  lr = *Lstk (Top - 1);
  k = gestionVar (lr);
  t = Top - 2;
  C2F(intersci).ntypes[t] = '$';
  C2F(intersci).iwhere[t] = lr;
  
  if (k == -1)
    {
      CANCEL ();
      Scierror (9999, "The type of the variable 1 is not managed by SciMax\r\n");
      return -1;
    } 
  
  determineOp (stri[9] - 65);
  
  lr = *Lstk (Top);
  k = gestionVar (lr);
  t = Top - 1;
  C2F(intersci).ntypes[t] = '$';
  C2F(intersci).iwhere[t] = lr;
  
  if (k == -1)
    {
      CANCEL ();
      Scierror (9999, "The type of the variable 2 is not managed by SciMax\r\n");
      return -1;
    } 
  
  Putc (')', is);
  Putc ('$', is);
  Putc ('\n', is);
  fflush (is);

  return recupResult (pos);
}

inline void 
determineOp (op)
     char op;
{
  int *hi = istk (iadr (*Lstk (Top - 1)));
  int *hj = istk (iadr (*Lstk (Top)));
  int a,b;
  
  if (hi[0] == 17 && hi[1] == 3 && hi[14] == 28 && hi[15] == 34 && hi[16] == 22)
    a = hi[31] * hi[32] - 1;
  else a = hi[1] * hi[2] - 1;
  if (hj[0] == 17 && hj[1] == 3 && hj[14] == 28 && hj[15] == 34 && hj[16] == 22)
    b = hj[31] * hj[32] - 1;
  else b = hj[1] * hj[2] - 1;
  
  switch (op)
    {
    case __ADD :
      Putc ('+', is);
      return;
    case __POW :
      Putc ('^', is);
      if (a) Putc ('^', is);
      return;
    case __MULT :
      if (a && b) Putc ('.', is);
      else Putc ('*', is);
      return;
    case __DIV :
      if (b)
	{
	  Putc (!a ? '*' : '.', is);
	  Putc ('i', is);
	  Putc ('n', is);
	  Putc ('v', is);
	}
      else Putc ('/', is);
      return;
    case __SUB :
      Putc ('-', is);
      return;
    case __BACKSLASH :
      if (a)
	{
	  Putc ('v', is);
	  Putc ('n', is);
	  Putc ('i', is);
	  Putc (!b ? '*' : '.', is);
	}
      else 
	{
	  Putc ('_', is);
	  Putc ('b', is);
	  Putc ('_', is);
	}
      return;
    case __PMULT :
      Putc ('*', is);
      return;
    case __PDIV :
      Putc ('/', is);
      return;
    case __PBACKSLASH :
      Putc ('_', is);
      Putc ('b', is);
      Putc ('_', is);
      return;
    case __PPOW :
      if (!b) Putc ('^', is);
      else
	{
	  Putc ('_', is);
	  Putc ('p', is);
	  Putc ('_', is);
	}
      return;
    case __FEEDBACK :
      Putc ('_', is);
      Putc ('f', is);
      Putc ('_', is);
      return;
    case __KRONPROD :
      Putc ('_', is);
      Putc ('k', is);
      Putc ('_', is);
      return;
    case __LOW :
      Putc ('<', is);
      return;
    case __LEQ :
      Putc ('<', is);
      Putc ('=', is);
      return; 
    case __GREAT :
      Putc ('>', is);
      return;
    case __GEQ :
      Putc ('>', is);
      Putc ('=', is);
      return; 
    case __NEQ :
      Putc ('#', is);
      return;
    case __EQ :
      Putc ('=', is);
      return;
    case __AFFECT :
      Putc (':', is);
      return;
    }
}
