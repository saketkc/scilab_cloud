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
#include "maxsci1.h"
#include "maxsci.h"

// a commenter ou decommenter selon version Scilab, la seconde est pour version >=5
//Scilab 4
//#include "xsci/x_ptyxP.h"
//#include "xsci/x_data.h"
//#define MAXCOLS term->screen.max_col
//Scilab 5
//#include "scilines.h"
#define MAXCOLS getColumnsSize()

extern int detecteErreurs (void);
extern void envoiDonnees (void);
extern void CANCEL (void);
extern int gestionVar (int);

int maxprint (void)
{
  int n;

  G_nb.vars = 0;
  G_nb.appels = 0;

  fprintf (is, "linel:%i$___(", MAXCOLS);

  n = gestionVar (*Lstk (Top));
  C2F(intersci).ntypes[Top - 1] = '$';
  C2F(intersci).iwhere[Top - 1] = *Lstk (Top);
  
  if (n == -1)
    {
      CANCEL ();
      return -1;
    }
  
  Putc (')', is);
  Putc ('$', is);
  Putc ('\n', is);
  fflush (is);

  n = detecteErreurs ();
  if (n == -1 || n == 1)
    return n;
  
  while ((VIDEOS, iseo (buf) == 0))
    sciprint ("%s", buf);
  
  return 0;
}
