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
extern int gestionVar (int add);
extern int recupResult (int pos);
extern void CANCEL (void);

int sym (pos)
     int pos;
{
  int k;
  
  G_nb.vars = 0;
  G_nb.appels = 0;
  
  Putc ('_', is);
  Putc ('(', is);

  k = gestionVar (*Lstk (Top));
  C2F(intersci).ntypes[Top - 1] = '$';
  C2F(intersci).iwhere[Top - 1] = *Lstk (Top);
  
  if (k == -1)
    {
      CANCEL ();
      C2F(overload) (&Top, "sym", 3);
      return -1;
    }
  
  Putc (')', is);
  Putc ('$', is);
  Putc ('\n', is);
  fflush (is);
  
  return recupResult (pos);
}

