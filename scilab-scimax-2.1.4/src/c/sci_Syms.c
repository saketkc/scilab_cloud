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
#include "maxsci1.h"

int
sci_Syms (fname)
     char *fname;
{
  int m, n, i, j, r, inj, pos = Rhs + 1;
  char **scivars;
  char *ch;
  char c;  
  
  if (max_is_ok == 0)
    {
      Scierror (9999, "Maxima has not been started : use maxinit\n");
      return -1;
    }
  if (quest_mode == 1)
    {
      Scierror (9999, "You must answer to the question !\n");
      return -1;
    }

  CheckLhs (1, 1);
  
  for (r = 1; r <= Rhs; r++)
    {
      GetRhsVar (r, SMD, &m, &n, &scivars);
      for (i = 0 ; i < m; i++)
	{
	  for (j = 0; j < n; j++)
	    { 
	      inj = i * n + j;
	      ch = scivars[inj];
	      if ((c = (char)(*(ch++))) != '\0' && (isalpha (c) != 0 ||
						    c == '%' || c == '_' ||
						    c == '#' || c == '!' ||
						    c == '$' || c == '?'))
		{
		  while (((c=(char)(*(ch++))) != '\0') && (isalnum (c) != 0 ||
							   c == '_' || c == '#' ||
							   c == '!' || c == '$' ||
							   c == '?'));
		  if (c != '\0')
		    {
		      Scierror (9999, "Error : invalid name for the variable %s\r\n", scivars[inj]);
		      return -1;
		    }
		}
	      else 
		{
		  Scierror (9999, "Error : invalid name for the variable %s\r\n", scivars[inj]);
		  return -1;
		}
	      creerSym (pos, scivars[inj], NULL, strlen (scivars[inj]), 1, 'M');
	      PutVar (pos, scivars[inj]);
	      ++pos;
	    }
	}
    }
  LhsVar (1) = 0;
  return 0;
}
