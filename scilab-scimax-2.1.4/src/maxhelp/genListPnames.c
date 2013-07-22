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
#include <stdlib.h>
#include <string.h>

typedef struct LISTPNAMES
{
  char * maxnam;
  char * scinam;
  struct LISTPNAMES * next;
} LISTPNAMES;

LISTPNAMES * pNames = NULL;

void
freeList (lpn)
     LISTPNAMES * lpn;
{
  if (lpn)
    {
      free (lpn->maxnam);
      free (lpn->scinam);
      freeList (lpn->next);
      if (lpn->next)
	free (lpn->next);
    }
}

char*
searchPnames (maxnam)
     char * maxnam;
{
  LISTPNAMES * lpn = pNames;
  
  while (lpn)
    {
      if (!strcmp (maxnam, lpn->maxnam))
	return lpn->scinam;
      lpn = lpn->next;
    }
  return NULL;
}

void
freeListPnames ()
{
  if (pNames)
    {
      freeList (pNames);
      free (pNames);
    }
}

void
genListPnames (file)
     char * file;
{
  FILE * fd;
  LISTPNAMES * lpn, * slpn;
  char buf1[256], buf2[256];
  fd = fopen (file, "r");
    
  if (!fd)
    {
      fprintf (stderr, "Error : file %s doesn't exist !\n", file);
      exit (0);
      return;
    }

  pNames = malloc (sizeof (LISTPNAMES));
  lpn = pNames;
  slpn = lpn;
  while (fscanf (fd, "%[^,],%[^,\n]\n", buf1, buf2) != EOF)
    {
      lpn->maxnam = strdup (buf1);
      lpn->scinam = strdup (buf2);
      lpn->next = malloc (sizeof (LISTPNAMES));
      slpn = lpn;
      lpn = lpn->next;
    }
  if (lpn != pNames)
    {
      free (slpn->next);
      slpn->next = NULL;
    }
  else
    {
      free (pNames);
      pNames = NULL;
    }
  fclose (fd);
}
    
