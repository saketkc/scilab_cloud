//    <Overload, a Scilab toolbox to overload Scilab's macros.>
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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mex.h"
#include "stack-c.h"
#include "sci_dynlib.h"
#include "Scierror.h"
#include "overstack.h"
//#include "Funtab.h"

#ifdef _MSC_VER
#define snprintf _snprintf

extern int cvstr_();
extern int intload_();
#endif

/* A voir : l'effacement d'une fonction overloadee (pb avec nb => id de place dispo)
 */


// a commenter ou decommenter selon version Scilab, la seconde est pour version >=5
//Scilab 4
//#define Funtab(id,fptr,job) C2F(funtab)(id,fptr,job)
//Scilab 5
extern int C2F(funnam) (int *id, char *fname, int *lp, int len);
extern int C2F(funtab)(int *id, int *fptr, int *job, char *namefunction, unsigned long namefunction_len);

#define FUNTAB(id,fptr,job,name) C2F(funtab)(id, fptr, job, name, strlen(name))

#define idstk(x,y) (C2F(vstk).idstk+(x-1)+(y-1)*nsiz)

extern C2F(overfuns) (int *);
int __overl__ (char *);
int __rien__ (char *);
int gererMacros (char *, int, int, char **);

extern GenericTable OverloadTab[MAXFUNINLIB];
static int nb = 2;
static int zero = 0, un = 1, deux = 2, trois = 3, quatre = 4, cinq = 5;

int sci_overload (char *fname)
{
  int nom[nsiz], nom1[nsiz], fptr, fptr1;
  int m, n, len;
  int id[nsiz] = {0, 0};
  int interf;
  char *name;
  char **tab, **tab1;

  if (nb == MAXFUNINLIB)
    {
      Scierror (9999,"Too many overloaded functions\r\n");
      return -1;
    }

  CheckRhs (0, 2);

  if (Rhs == 0)
    {
      getSciTab (1);
      LhsVar (1) = 1;
      return 0;
    }

  GetRhsVar (1, "S", &m, &n, &tab1);

  if (n == 2)
    setSciTab (tab1, m);
  else if ( m != 1 && n != 1 )
    {
      Scierror (999,"overload: Bad first argument\r\n");
      return 0;
    }

  len = strlen (tab1[0]);
  name = malloc (25);
  strncpy (name, tab1[0], 25);

  if (Rhs == 2)
    {
      GetRhsVar (2, "S", &m, &n, &tab);
      if ( m != 1 || n == 0 )
        {
          free (name);
          Scierror (999,"overload: bad number of rows\r\n");
          return 0;
        }
      if (gererMacros (name, m, n, tab) == -1)
        {
          free (name);
          return 0;
        }
    }

  C2F(cvname) (nom1, name, &zero, len);
  FUNTAB (nom1, &fptr1, &un, name);
  if (fptr1 != 0)
    FUNTAB (nom1, &fptr1, &quatre, name);
  C2F(cvname) (nom, "overload", &zero, 8);
  FUNTAB (nom, &fptr, &un, "overload");
  interf = (int)(fptr / MAXFUNINLIB);
  fptr = MAXFUNINLIB * interf + nb;
  FUNTAB (nom1, &fptr, &trois, name);

  OverloadTab[nb - 1].f = (Myinterfun)sci_gateway;
  OverloadTab[nb - 1].F = (GT)(__overl__);
  OverloadTab[nb - 1].name = name;

  ++nb;

  return 0;
}

int gererMacros (char *name, int m, int n, char **typ)
{
  int fin, i, tops = strlen (name);
  char nm[25];
  int id[nsiz], id1[nsiz];

  C2F(cvname) (id, name, &zero, strlen (name));
  C2F(com).fin = 0;
  tops = Top;
  Top = Top - Rhs + 2;
  C2F(overfuns) (id);
  Top = tops;
  if (C2F(com).fin == 0)
    {
      Scierror (999, "overload: %s is not a Scilab function\r\n", name);
      return -1;
    }
  fin = C2F(com).fin;
  if (C2F(com).fun > 0)
    {
      Scierror (999, "overload: %s is not a Scilab macro\r\n", name);
      return -1;
    }

  C2F(com).fin = 0;
  C2F(com).fun = 0;

  //On renomme funnam en %<type_var_1>_funnam
  snprintf (nm, 25, "%%%s_%s", typ[0], name);
  C2F(cvname) (id, nm, &zero, strlen (nm));
  C2F(putid) (&C2F(vstk).idstk[(fin - 1) * nsiz], id);

  for (i = 4; i < n + 3; i++)
    {
      snprintf (nm, 25, "%%%s_%s", typ[i - 3], name);
      C2F(cvname) (id1, nm, &zero, strlen (nm));
      insOT (id1, id);
    }

  return 0;
}

int __overl__(char *fname)
{
  int lp;
  int id[nsiz], *id1;

  lp = iadr (*Lstk (1 + Top - Rhs));
  C2F(funnam) (id, fname, &lp, strlen (fname));

  Fin = -1;
  C2F(stackg) (id);
  if (Err > 0)
    return 0;
  if (Fin != 0)
    id1 = id;
  else
    {
      id1 = getassoc (id);
      if (id1 == NULL)
        id1 = id;
    }

  C2F(putid) (&C2F(recu).ids[C2F(recu).pt * nsiz], id1);
  C2F(com).fun = -1;
  return 0;
}

int __rien__(char *fname)
{
  Scierror (9999, "You should re-overload the function\r\n");
  return 0;
}
