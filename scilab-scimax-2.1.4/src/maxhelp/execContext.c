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

#define MAXSTACK 64
#define MAXBUF 4096
#define TRUE 1
#define FALSE 0

extern int nblines;
extern char deffnmode;
extern char deffnxmode;
extern char defvrmode;
extern char examplemode;

static char buffer[MAXBUF];
static int posbuf = 0, ptrbuf = 0;

static void * stack[MAXSTACK];
static int Tops = -1;

static int execStk[MAXSTACK];
static int Topes = -1;

static int bufStk[MAXSTACK];
static int Topbufs = -1;

/* The braces are normally used to delimit an argument and when you want 
   to print a brace you should use @{ or @}. Unfortunatelly in @tex mode or in
   @iftex mode braces can be used as normal chars. */
static char braceStk[MAXSTACK] = {TRUE};
static int Topbs = 0;
#define currentBmode (braceStk[Topbs])

/* prevBmode is only used in insertRbrace which necessarly called after
   insertLbrace which pushes a boolean to the stack so Topbs > 1.
   This is conform to the grammar which considers only expressions of the kind 
   { text }. In @tex mode, user must close all { by }, the expressions of the kind
   \left\{\sum ...\right. should be closed by %}. */
#define prevBmode (braceStk[Topbs - 1])

extern int execCommand (char *, char **);
extern void insertText (char *);
extern freeListNames (void);

void pushs (void *);
void pushes (int);
void popes (void);
void pushbs (char);
void popbs (void);
int getNbarg (void);
void * getArg (int);
void enterCommandMode (char *);
void closeCommandMode ();
void insertWhite (char *);
void insertLBrace (void);
void insertRBrace (void);
void insertStr (char *);
void insertStr2 (char *);
void pushArg (void);
void closePara (void);

void
pushs (ptr)
void * ptr;
{
    ++Tops;
    stack[Tops] = ptr;
}

void
pops ()
{
    if (stack[Tops] != NULL)
	free (stack[Tops]);
    --Tops;
}

void
pushes (n)
int n;
{
    ++Topes;
    execStk[Topes] = n;
}

void
popes ()
{
    --Topes;
}

void
pushbufs (m, n)
int m, n;
{
    bufStk[Topbufs + 1] = m;
    bufStk[Topbufs + 2 ] = n;
    Topbufs += 2;
}

void
popbufs ()
{
    Topbufs -= 2;
}

void
pushbs (n)
char n;
{
    ++Topbs;
    braceStk[Topbs] = n;
}

void
popbs ()
{
    --Topbs;
}

int
getNbArg ()
{
    return Tops - execStk[Topes];
}

void*
getArg (n)
int n;
{
    if (execStk[Topes] + n> Tops)
	return NULL;
    return stack[execStk[Topes] + n];
}

/* When we have a @deffn or a @deffnx command, we need to have the number
   of arguments and the function's name to generate the file listmaxfun.sce */
void
enterCommandMode (com)
char * com;
{
    if (!strcmp (com, "@deffn"))
	deffnmode = 1;
    else if (!strcmp (com, "@deffnx"))
	deffnxmode = 1;
    else if (!strcmp (com, "@defvr"))
	defvrmode = 1;
    else if (!strcmp (com, "@example"))
	examplemode = 1;

    pushs (com);
    pushbufs (posbuf, ptrbuf);
    ptrbuf = posbuf;
    pushes (Tops);
    pushbs (FALSE);
}

void
printStack ()
{
    int i;
    fprintf (stdout, "Stack :\n");
    for (i=0;i<=Tops;i++)
    {
	fprintf (stdout, "stack[%i]=%s\n", i, stack[i]);
    }
}

void 
clearCom ()
{
    Tops = execStk[Topes] - 1;
    free (stack[execStk[Topes]]);
    popes ();
    posbuf = bufStk[Topbufs - 1];
    ptrbuf = bufStk[Topbufs];
    popbufs ();
    if (Topes == -1)
    {
	posbuf = 0;
	ptrbuf = 0;
    }
    popbs ();
}  

void
closeCommandMode ()
{
    char * res;
  
    pushArg ();
    if (!execCommand ((char*)(stack[execStk[Topes]]), &res))
    {
	fprintf (stderr, "An error occured with command %s at line %i\n",
		 (char*)(stack[execStk[Topes]]), nblines);
	freeListNames ();
	exit (0);
	return;
    }
    clearCom ();
    insertStr (res); 
}

void
insertWhite (wh)
char * wh;
{
    if (currentBmode)
	insertStr (wh);
    else 
    {
	pushArg ();
	free (wh);
    }
}

void
insertLBrace ()
{
    if (currentBmode)
	insertStr2 ("{");
    pushbs (TRUE);  
}

void
insertRBrace ()
{
    if (prevBmode)
	insertStr2 ("}");
    popbs ();
}

/* This function put a string to the stack or insert it in a file (cf 
   insertText in texiIinterface.c). It supposes that the string has been mallocated */
void
insertStr (str)
char * str;
{
    if (str)
    {
	insertStr2 (str);
	free (str);
    }
}

void
insertStr2 (str)
char * str;
{
    if (Topes != -1)
	posbuf += sprintf (buffer + posbuf, "%s", str);
    else insertText (str);
}

void
pushArg ()
{
    if (ptrbuf != posbuf)
    {
	++posbuf;
	pushs (buffer + ptrbuf);
	ptrbuf = posbuf;
    }
}


