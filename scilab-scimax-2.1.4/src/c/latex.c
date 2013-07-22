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
extern int detecteErreurs (void);
extern void CANCEL (void);
extern int gestionVar (int);

int
latex (stro, m)
     char **stro;
     int *m;
{
  int k, len, t, lr;
  char *ch;
  char b;
  
  G_nb.vars = 0;
  G_nb.appels = 0;
  
  Putc ('_', is);
  Putc ('t', is);
  Putc ('(', is);

  lr = *Lstk (Top);
  k = gestionVar (lr);
  t = Top - 1; 
  C2F(intersci).ntypes[t] = '$';
  C2F(intersci).iwhere[t] = lr;
  
  if (k == -1)
    {
      CANCEL ();
      C2F(overload) (&Top, "latex", 5);
      return -1;
    }
  
  Putc (')', is);
  Putc ('$', is);
  Putc ('\n', is);
  fflush (is);

  // On detecte les erreurs
  k = detecteErreurs ();
  if (k == -1)
    return -1;
  else if (k == 1)
    {
      *stro = malloc (0);
      return 0;
    }
  
  // On attend puis on recupere la longueur de la reponse (pour le malloc) et enfin on met la reponse dans *stro
  len = atoi (buf + 4);
  
  // On rajoute 2 pour le '\n' en fin de chaine
  *stro = malloc (len + 2);
  fread (*stro, len + 2, 1, os);
  (*stro)[len] = '\0';
  
  VIDEOS;
  return 0;
}
