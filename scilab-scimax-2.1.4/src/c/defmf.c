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

extern int detecteErreurs (void);

int
defmf (maxname, maxcode, m, n, scicode, sciname, scifun)
     char *maxname, *maxcode, **scicode, *sciname, **scifun;
     int m, n;
{
  int nbargs, i, len;
  char *ch, *ch1, *ch2;

  G_nb.vars = 0;
  G_nb.appels = 0;
  
  fprintf (is, "__scifun(%s:=(%s))$\n", maxname, maxcode);
  fflush (is);

  // On detecte les erreurs
  if (detecteErreurs () == -1)
    return -1;
  
  // On attend puis on recupere la longueur de la reponse (pour le malloc) et enfin on met la reponse dans *stro
  VIDEOS;
  ch = buf;
  while ((++ch)[0] != '&');
  ch[0] = '\0';
  ch1 = ch++;
  nbargs = atoi (buf);
  while ((++ch1)[0] != '\n');
  ch1[0] = '\0';
  len = ch1 - ch;
  *scicode = malloc ((2 * (nbargs == -1? 1 : nbargs) + 62 + len) * sizeof (char));
  ch1 = *scicode;
  *scifun = malloc ((2 * (nbargs == -1 ? 1 : nbargs) + 15 + strlen (sciname)) * sizeof (char));
  ch2 = *scifun;
  if (nbargs != -1)
    {
      ch1 += sprintf (ch1, "if argn(2)~=%i then error(42), end;", nbargs);
      ch1 += sprintf (ch1, "%c=maxevalf('%s',",'a' + nbargs, ch);
      ch2 += sprintf (ch2, "%c=%s(" , 'a' + nbargs, sciname);
      for (i = 0; i < nbargs - 1; i++)
	{
	  ch1 += sprintf (ch1, "%c,", 'a' + i);
	  ch2 += sprintf (ch2, "%c,", 'a' + i);
	}
      sprintf (ch1, "%c)\0", 'a' + nbargs - 1);
      sprintf (ch2, "%c)\0", 'a'+ nbargs - 1);
    }
  else
    {
      sprintf (ch1, "a=maxevalfl('%s',varargin)\0", ch);
      sprintf (ch2, "a=%s(varargin)\0", sciname);
    }
  VIDEOS;
  return 0;
}
