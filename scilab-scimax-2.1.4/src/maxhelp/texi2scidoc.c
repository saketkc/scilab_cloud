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
#include <unistd.h>
#include <stdlib.h>

extern int yyparse (void);
extern void yyrestart (FILE *);

extern void freeListNames (void);
extern void printIgnoredComs (void);
extern void genListPnames (char *);
extern void freeListPnames (void);

extern char first_pass;
extern int nblines;
extern char * output_dir;
extern char * listmaxfun_dir;

/* We make two passes :
   - the first one is used to create a list of the xml files which will be
     generated
   - the second tests if the argument of @xref command is in the list 
     previously created. */

int
main (argc, argv)
     int argc;
     char * argv[];
{
  int i, j;
  FILE * fd;
  char c;
  char * perso = NULL;
  extern char * optarg;
  extern int optind;
  
  while ((c = getopt (argc, argv, "hs:l:p:")) != -1)
    {
      switch (c)
	{
	case 's' :
	  output_dir = optarg; 
	  break;
	case 'l' :
	  listmaxfun_dir = optarg;
	  break;
	case 'p' :
	  perso = optarg;
	  break;
	default :
	  fprintf (stdout, "texi2scidoc [-s sdir] [-l ldir] [-p perso] files\n\n");
	  fprintf (stdout, "\t- sdir is the ouput directory for xml files.\n");
	  fprintf (stdout, "\t  If omitted, the files will be put in the current directory.\n\n"); 
	  fprintf (stdout, "\t- ldir is the directory where to put listmaxfun.sce.\n");
	  fprintf (stdout, "\t  If omitted, no listmaxfun.sce.\n\n");
	  fprintf (stdout, "\t- perso is a file containing Maxima function names and their\n");
	  fprintf (stdout, "\t  associated Scilab names. The format must be :\n");
	  fprintf (stdout, "\t\tmaxName1,sciName1\n\t\tmaxName2,sciName2\n\t\t...\n");
	  fprintf (stdout, "\t  You can generate this file in executing in Scilab\n");
	  fprintf (stdout, "\t  the script genPnames.sce (you should eventually modify\n");
	  fprintf (stdout, "\t  the path for personnalizedNames.sce in the script).\n");
	  fprintf (stdout, "\t  If omitted, the personnalized names won't be considered.\n\n");
	  return 0;
	}
    }
  if (!output_dir)
    output_dir = ".";

  if (perso)
    genListPnames (perso);

  first_pass = 0;
  for (i = 0; i < 2; i++)
    {
      first_pass = !first_pass;
      if (!first_pass)
	listmaxfun_dir = NULL;
      for (j = optind; j < argc; j++)
	{
	  fd = fopen (argv[j], "r");
	  if (!fd)
	    {
	      fprintf (stderr, "The file %s doesn't exist !\n", argv[j]);
	      exit (0);
	      return;
	    }
	  if (first_pass)
	    fprintf (stdout, "Parsing %s...\n", argv[j]);
	  nblines = 0;
	  yyrestart (fd);
	  yyparse ();
	  fclose (fd);
	}
    }
  printIgnoredComs ();
  freeListNames ();
  freeListPnames ();
  return 0;
}
