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

extern void envoiDonnees (void);
extern int gestionVar (int);
extern void CANCEL (void);
extern int recupResult (int);

int
maxevalf (pos, stri)
     int pos;
     char *stri;
{
  int i, k, t, lr;
  
  G_nb.vars = 0;
  G_nb.appels = 0;
  
  fprintf (is, "_(%s(", stri);
  
  for (i = 2 + Top - Rhs; i <= Top; i++)
    {
      lr = *Lstk (i);
      k = gestionVar (lr);
      t = i - 1;
      C2F(intersci).ntypes[t] = '$';
      C2F(intersci).iwhere[t] = lr;
      
      if (k == -1)
	{
	  CANCEL ();
	  Scierror (9999, "The type of the variable %i is not managed by SciMax\r\n", i + Rhs - Top - 1);
	  return -1;
	}
      if (i != Top)
	Putc (',', is);
    }

  Putc (')', is);
  Putc (')', is);
  Putc ('$', is);
  Putc ('\n', is);
  fflush (is);

  return recupResult (pos);
}
