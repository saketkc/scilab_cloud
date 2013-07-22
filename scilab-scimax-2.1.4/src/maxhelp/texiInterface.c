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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAXSTACK 32

#define xmlbeg "<?xml version=\'1.0\' encoding=\'UTF-8\'?>\n<refentry version=\'5.0-subset Scilab\' xml:id=\'%s\' xml:lang=\'en\'\nxmlns=\'http://docbook.org/ns/docbook\'\nxmlns:xlink=\'http://www.w3.org/1999/xlink\'\nxmlns:svg=\'http://www.w3.org/2000/svg\'\nxmlns:ns3=\'http://www.w3.org/1999/xhtml\'\nxmlns:mml=\'http://www.w3.org/1998/Math/MathML\'\nxmlns:db=\'http://docbook.org/ns/docbook\'>\n<info><pubdate>$LastChangedDate$</pubdate></info>\n\n<refnamediv>\n<refname>%s</refname>\n<refpurpose>%s</refpurpose>\n</refnamediv>\n<refsynopsisdiv>\n"

extern int getNbArg (void);
extern void* getArg (int);
extern void insertStr2 (char *);
extern char* searchPnames (char *);

void insertText (char *);
int execCommand (char *, char **);
void insertAccent (char *, char *);
void enterSeeMode (char *);
void closeSeeMode (void);
void printIgnoredcoms (void);

typedef char* (*ATCOM) (void);

char * at_var (void);
char * at_code (void);
char * at_math (void);
char * at_anchor (void);
char * at_emph (void);
char * at_i (void);
char * at_b (void);
char * at_t (void);
char * at_w (void);
char * at_file (void);
char * at_email (void);
char * at_include (void);
char * at_noindent (void);
char * at_kbd (void);
char * at_asis (void);
char * at_dfn (void);
char * at_image (void);
char * at_ref (void);
char * at_pxref (void);
char * at_key (void);
char * at_url (void);
char * at_sp (void);
char * at_bullet (void);
char * at_minus (void);
char * at_deffn (void);
char * at_end_deffn (void);
char * at_deffnx (void);
char * at_defvr (void);
char * at_end_defvr (void);
char * at_defvrx (void);
char * at_fnindex (void);
char * at_vrindex (void);
char * at_example (void);
char * at_end_example (void);
char * at_verbatim (void);
char * at_end_verbatim (void);
char * at_menu (void);
char * at_end_menu (void);
char * at_table (void);
char * at_end_table (void);
char * at_item (void);
char * at_itemize (void);
char * at_end_itemize (void);
char * at_enumerate (void);
char * at_end_enumerate (void);
char * at_node (void);
char * at_ifinfo (void);
char * at_end_ifinfo (void);
char * at_ifnotinfo (void);
char * at_end_ifnotinfo (void);
char * at_ifhtml (void);
char * at_end_ifhtml (void);
char * at_html (void);
char * at_end_html (void);
char * at_tex (void);
char * at_end_tex (void);
char * at_flushleft (void);
char * at_end_flushleft (void);
char * at_iftex (void);
char * at_end_iftex (void);
char * at_ifnottex (void);
char * at_end_ifnottex (void);
char * at_section (void);
char * at_chapter (void);
char * at_appendix (void);
char * at_footnotestyle (void);
char * at_footnote (void);
char * at_smallformat (void);
char * at_end_smallformat (void);
char * at_printindex (void);
char * at_subsection (void);
char * at_subsubsection (void);
char * at_end (void);
char * at_item_in_table (void);
char * at_item_in_itemize (void);

typedef struct
{
    char com[32];
    ATCOM ptr;
} Command;

static Command acom[128] = {
    {"@var", &at_var},
    {"@code", &at_code},
    {"@math", &at_math},
    {"@anchor", &at_anchor},
    {"@image", &at_image},
    {"@emph", &at_emph},
    {"@i", &at_i},
    {"@b", &at_b},
    {"@t", &at_t},
    {"@w", &at_w},
    {"@file", &at_file},
    {"@email", &at_email},
    {"@include", &at_include},
    {"@footnote", &at_footnote},
    {"@noindent", &at_noindent},
    {"@kbd", &at_kbd},
    {"@key", &at_key},
    {"@asis", &at_asis},
    {"@dfn", &at_dfn},
    {"@ref", &at_ref},
    {"@pxref", &at_pxref},
    {"@url", &at_url},
    {"@sp", &at_sp},
    {"@bullet", &at_bullet},
    {"@minus", &at_minus},
    {"@deffn", &at_deffn},
    {"@end_deffn", &at_end_deffn},
    {"@deffnx", &at_deffnx},
    {"@defvr", &at_defvr},
    {"@end_defvr", &at_end_defvr},
    {"@defvrx", &at_defvrx},
    {"@fnindex", &at_fnindex},
    {"@vrindex", &at_vrindex},
    {"@menu", &at_menu},
    {"@end_menu", &at_end_menu},
    {"@table", &at_table},
    {"@end_table", &at_end_table},
    {"@item", &at_item},
    {"@itemize", &at_itemize},
    {"@end_itemize", &at_end_itemize},
    {"@enumerate", &at_enumerate},
    {"@end_enumerate", &at_end_enumerate},
    {"@example", &at_example},
    {"@end_example", &at_end_example},
    {"@smallformat", &at_smallformat},
    {"@end_smallformat", &at_end_smallformat},
    {"@verbatim", &at_verbatim},
    {"@end_verbatim", &at_end_verbatim},
    {"@node", &at_node},
    {"@section", &at_section},
    {"@chapter", &at_chapter},
    {"@appendix", &at_appendix},
    {"@footnotestyle", &at_footnotestyle},
    {"@printindex", &at_printindex},
    {"@subsection", &at_subsection},
    {"@subsubsection", &at_subsubsection},
    {"@ifinfo", &at_ifinfo},
    {"@end_ifinfo", &at_end_ifinfo},
    {"@ifnotinfo", &at_ifnotinfo},
    {"@end_ifnotinfo", &at_end_ifnotinfo},
    {"@ifhtml", &at_ifhtml},
    {"@end_ifhtml", &at_end_ifhtml},
    {"@html", &at_html},
    {"@end_html", &at_end_html},
    {"@tex", &at_tex},
    {"@end_tex", &at_end_tex},
    {"@flushleft", &at_flushleft},
    {"@end_flushleft", &at_end_flushleft},
    {"@iftex", &at_iftex},
    {"@end_iftex", &at_end_iftex},
    {"@ifnottex", &at_ifnottex},
    {"@end_ifnottex", &at_end_ifnottex},
    {"@end", &at_end},
    {"", (ATCOM)NULL}
};

static FILE * fd, * listmaxfun = NULL;
static char * table_com;
static char itemize_com = 0;
static int nbitems = 0;

static char stackw[MAXSTACK] = {0};
static int topsw = 0;
#define writemode (stackw[topsw])

static char stackp[MAXSTACK] = {1};
static int topsp = 0;
#define paramode (stackp[topsp])
static char is_in_para = 0;
static char is_text;

static int stackit[MAXSTACK];
static int topit = -1;

static char see_mode = 0;

char first_pass;
char * output_dir = NULL;
char * listmaxfun_dir = NULL;

typedef struct LIST
{
    char * nam;
    char dup;
    struct LIST * next;
} LIST;

static LIST * names = NULL;
static LIST * currentNames;

static struct ARGS
{
    int nbargs;
    int nbargs_deffnx;
} args = {0, 0};

static char * currentFunNam = NULL;
char deffnmode = 0;
char deffnxmode = 0;
char defvrmode = 0;
char examplemode = 0;

extern int nblines;
extern void * pNames;

void 
freeNames (pn)
LIST * pn;
{
    if (pn == NULL)
	return;
    free (pn->nam);
    freeNames (pn->next);
    free (pn->next);
}

void
freeListNames ()
{
    freeNames (names);
    if (listmaxfun)
	fclose (listmaxfun);
}

LIST*
searchName (nam)
char * nam;
{
    LIST *sn = names;
  
    while (sn != NULL)
    {
	if (!strcmp (sn->nam, nam))
	    return sn;
	sn = sn->next;
    }
    return NULL;
}

void 
addName (nam, typ)
char * nam;
int typ;
{
    LIST * sn = searchName (nam);
  
    if (sn)
    {
	if (sn->dup > 0)
	    ++sn->dup;
	else 
	    --sn->dup;
	return;
    }
    if (!names)
    {
	names = malloc (sizeof (LIST));
	names->nam = strdup (nam);
	names->dup = 1;
	currentNames = names;
	return;
    }
    currentNames->next = malloc (sizeof (LIST));
    currentNames = currentNames->next;
    currentNames->nam = strdup (nam);
    currentNames->dup = typ;
    currentNames->next = NULL;
}

void
printIgnoredComs ()
{
    LIST *sn = names;
    char n = 0;
  
    while (sn != NULL)
    {
	if (sn->dup < 0)
	{
	    if (!n)
	    {
		fprintf (stderr, "\nWarning : the following commands were ignored :\n");
		n = 1;
	    }
	    fprintf (stderr, "   - %s has been encountered %i times\n", sn->nam, - sn->dup);
	} 
	sn = sn->next;
    }
}
  
void
addFun2List ()
{
    if (listmaxfun_dir && first_pass && !strpbrk (currentFunNam, "+*&^!#.:=?\'") && currentFunNam[0] != '_')
    {
	if (!listmaxfun)
	{
	    char * str = malloc (strlen (listmaxfun_dir) + 1 + 14 + 1);
	    sprintf (str, "%s/listmaxfun.sce", listmaxfun_dir);
	    listmaxfun = fopen (str, "w");
	    free (str);
	    fprintf (listmaxfun, "//This file has been generated automatically from the Maxima\n//documentation.\n//Don't modify it !\n//You can add other functions in the file personnalizedMaxfun.sce\n\n");
	}
      
	fprintf (listmaxfun, "createmaxfun(\'%s\',%i)\n", currentFunNam, args.nbargs);
    }
    free (currentFunNam);
}

void
pushsw (n)
char n;
{
    ++topsw;
    stackw[topsw] = n;
}

void
popsw ()
{
    --topsw;
}

void
pushsp (n)
char n;
{
    ++topsp;
    stackp[topsp] = n;
}

void
popsp ()
{
    --topsp;
}

void
pushit (n)
char n;
{
    ++topit;
    stackit[topit] = n;
}

void
popit ()
{
    --topit;
}

void
insertLdots ()
{
    if (deffnmode || deffnxmode)
	args.nbargs = -1;
    insertStr2 ("...");
}
  
void
insertText (str)
char * str;
{
    if (!first_pass && writemode)
    {
	if (!paramode)
	{
	    if (is_in_para)
	    {
		fprintf (fd, "</para>%s", str);
		is_in_para = 0;
	    }
	    else 
		fprintf (fd, "%s", str);
	}
	else
	{
	    if (is_in_para)
	    {
		if (is_text)
		    fprintf (fd, "%s", str);
		else 
		{
		    is_in_para = 0;
		    is_text = 1;
		    fprintf (fd, "</para>\n%s", str);
		}
	    }
	    else
		if (is_text)
		{
		    is_in_para = 1;
		    fprintf (fd, "<para>%s", str);
		}
		else 
		{
		    is_text = 1;
		    fprintf (fd, "%s", str);
		}
	}
    }
}

void
closePara ()
{
    if (!first_pass && writemode && paramode && is_in_para)
    {
	is_in_para = 0;
	fprintf (fd, "</para>\n");
    }
}

void
insertAccent (acc, str)
char * acc, * str;
{
    char ch[2] = {str[0], '\0'}; 
    insertText (ch);
    free (str);
}

int
execCommand (com, res)
char * com;
char ** res;
{
    int i;

    //fprintf (stdout,"ligne:%i,com=%s\n",nblines,com);
  
    for (i = 0; acom[i].com[0] != '\0'; i++)
	if (!strcmp (acom[i].com, com))
	    break;
    if (acom[i].com[0] != '\0')
	*res = acom[i].ptr ();
    else 
    {
	addName (com, -1);
	*res = NULL;
    }
    return 1;
}

void
enterSeeMode (str)
char * str;
{
    see_mode = 1;
    insertText (str);
}

void
closeSeeMode ()
{
    see_mode = 0;
}

char *
modifyName (nam)
char * nam;
{
    char * str;
    char * namm = malloc (256);
    char * save = namm;

    for (nam; nam[0] != '\0'; nam++)
    {
	switch (nam[0])
	{
	case '+' :
	    namm += sprintf (namm, "PLUS");
	    break;
	case '*' :
	    namm += sprintf (namm, "STAR");
	    break;
	case '&' :
	    if (nam[1] == 'l') namm += sprintf (namm, "LOWER");
	    else if (nam[1] == 'g') namm += sprintf (namm, "GREATER");
	    nam += 3;
	    break;
	case '<' :
	    str = strchr (nam + 1, '<');
	    str[0] = '\0';
	    sprintf (namm, "%s", strchr (nam + 2, '>') + 1);
	    str[0] = '<';
	    nam = modifyName (namm) - 1;
	    break;
	case '^' :
	    namm += sprintf (namm, "POW");
	    break;
	case '!' :
	    namm += sprintf (namm, "EXCLAM");
	    break;
	case '#' :
	    namm += sprintf (namm, "SHARP");
	    break;
	case '.' :
	    namm += sprintf (namm, "DOT");
	    break;
	case ':' :
	    namm += sprintf (namm, "COLON");
	    break;
	case '=' :
	    namm += sprintf (namm, "EQUAL");
	    break;
	case '?' :
	    namm += sprintf (namm, "QUESTION");
	    break;
	case '%' :
	    namm += sprintf (namm, "PERCENT");
	    break;
	case '\'' :
	    namm += sprintf (namm, "QUOTE");
	    break;
	case '`' :
	    namm += sprintf (namm, "BQUOTE");
	    break;
	case '|' :
	    namm += sprintf (namm, "PIPE");
	    break;
	case '~' :
	    namm += sprintf (namm, "TILDE");
	    break;
	case '[' :
	    namm += sprintf (namm, "BRACKET");
	    break;
	default :
	    namm[0] = nam[0];
	    ++namm;
	}
    }
    namm[0] = '\0';
    return save;
}

char *
modifyNameForRefname (nam)
char * nam;
{
    char * str;
    char * namm = malloc (256);
    char * save = namm;

    for (nam; nam[0] != '\0'; nam++)
    {
	switch (nam[0])
	{
	case '+' :
	    namm += sprintf (namm, "PLUS ");
	    break;
	case '*' :
	    namm += sprintf (namm, "STAR ");
	    break;
	case '&' :
	    if (nam[1] == 'l') namm += sprintf (namm, "LOWER ");
	    else if (nam[1] == 'g') namm += sprintf (namm, "GREATER ");
	    nam += 3;
	    break;
	case '<' :
	    str = strchr (nam + 1, '<');
	    str[0] = '\0';
	    sprintf (namm, "%s", strchr (nam + 2, '>') + 1);
	    str[0] = '<';
	    nam = modifyNameForRefname (namm) - 1;
	    break;
	case '^' :
	    namm += sprintf (namm, "POW ");
	    break;
	case '!' :
	    namm += sprintf (namm, "EXCLAM ");
	    break;
	case '#' :
	    namm += sprintf (namm, "SHARP ");
	    break;
	case '.' :
	    namm += sprintf (namm, "DOT ");
	    break;
	case ':' :
	    namm += sprintf (namm, "COLON ");
	    break;
	case '=' :
	    namm += sprintf (namm, "EQUAL ");
	    break;
	case '?' :
	    namm += sprintf (namm, "QUESTION ");
	    break;
	case '\'' :
	    namm += sprintf (namm, "QUOTE ");
	    break;
	case '`' :
	    namm += sprintf (namm, "BQUOTE ");
	    break;
	case '|' :
	    namm += sprintf (namm, "PIPE ");
	    break;
	case '~' :
	    namm += sprintf (namm, "TILDE ");
	    break;
	case '[' :
	    namm += sprintf (namm, "BRACKET ");
	    break;
	default :
	    namm[0] = nam[0];
	    ++namm;
	}
    }
    namm[0] = '\0';
    return save;
}

char*
at_var ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@var");
    if (arg > 1)
	return NULL;
    if (listmaxfun_dir && args.nbargs != -1)
    {
	if (deffnmode)
	    ++args.nbargs;
	else if (deffnxmode)
	    ++args.nbargs_deffnx;
    }

    str = getArg (1);
    if (!deffnmode && !deffnxmode && !defvrmode)
    {
	xml = malloc (strlen (str) + 13 + 14 + 1);
	sprintf (xml, "<replaceable>%s</replaceable>", str);
    }
    else 
    {
	xml = strdup(str);
    }

    return xml;
}

char*
at_code ()
{
    if (see_mode)
	return at_ref ();
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@code");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    if (!deffnmode && !deffnxmode && !defvrmode && !examplemode)
    {
	xml = malloc (strlen (str) + 9 + 10 + 1);
	sprintf (xml, "<literal>%s</literal>", str);
    }
    else
    {
	xml = strdup(str);
    }
    return xml;
}

char*
at_math ()
{
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@math");
    if (arg > 1)
	return NULL;
    return strdup (getArg (1));
}

char*
at_pxref ()
{
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@pxref");
    if (arg > 1)
	return NULL;
    return strdup (getArg (1));
}

char*
at_i ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@i");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 10 + 11 + 1);
    sprintf (xml, "<emphasis>%s</emphasis>", str);
    return xml;
}

char*
at_footnote ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@footnote");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 10 + 11 + 1);
    sprintf (xml, "<emphasis>%s</emphasis>", str);
    return xml;
}

char*
at_b ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@b");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 22 + 11 + 1);
    sprintf (xml, "<emphasis role=\'bold\'>%s</emphasis>", str);
    return xml;
}

char*
at_t ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@t");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 9 + 10 + 1);
    sprintf (xml, "<literal>%s</literal>", str);
    return xml;
}

char*
at_w ()
{
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@w");
    if (arg > 1)
	return NULL;
    return strdup (getArg (1));
}


char*
at_file ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@file");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 10 + 11 + 1);
    // TODO replace literal by filename
    sprintf (xml, "<literal>%s</literal>", str);
    return xml;
}

char*
at_email ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@email");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 7 + 8 + 1);
    sprintf (xml, "<email>%s</email>", str);
    return xml;
}

char*
at_kbd ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@kbd");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 11 + 12 + 1);
    // TODO replace literal by userinput
    sprintf (xml, "<literal>%s</literal>", str);
    return xml;
}

char*
at_key ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@key");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 11 + 12 + 1);
    // TODO replace literal by userinput
    sprintf (xml, "<literal>%s</literal>", str);
    return xml;
}

char*
at_asis ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@asis");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 1);
    sprintf (xml, "%s", str);
    return xml;
}

char*
at_dfn ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@dfn");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 11 + 12 + 1);
    // TODO replace literal by firstterm
    sprintf (xml, "<literal>%s</literal>", str);
    return xml;
}

char*
at_emph ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@emph");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (strlen (str) + 10 + 11 + 1);
    sprintf (xml, "<emphasis>%s</emphasis>", str);
    return xml;
}

char*
at_image ()
{
    char * str, * xml, * comma;
    int arg = getNbArg ();
    if (arg != 1)
	return NULL;
    str = getArg (1);
    comma = strchr (str, ',');
    if (comma)
	comma[0] = '\0';
    xml = malloc (strlen (str) + 49 + 48 + 1);
    sprintf (xml, "<mediaobject><imageobject><imagedata fileref=\'%s.gif\' format=\'GIF\'/></imageobject></mediaobject>", str);
    return xml;
}

char*
at_anchor ()
{
    return NULL;
}

char*
at_include ()
{
    return NULL;
}

char*
at_ref ()
{
    char * str, * str1, * xml;
    LIST * sn;
    FILE * xmlFile = NULL;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@ref");
    if (arg > 1)
	return NULL;
  
    str = modifyName (getArg (1));
    sn = searchName (str);
    if (!sn || (sn->dup < 0))
    {
	free (str);
	str = getArg (1);
	xml = malloc (strlen (str) + 9 + 10 + 1);
	sprintf (xml, "<literal>%s</literal>", str);
	return xml;
    } 
    xml = malloc (strlen (str) + 15 + 3 + 1);
    sprintf (xml, "<xref linkend=\'%s\'/>", str);
    free (str);
    return xml;
}

char*
at_url ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg == 0)
	return strdup ("@url");
    if (arg > 1)
	return NULL;
    str = getArg (1);
    xml = malloc (2 * strlen (str) + 14 + 8 + 1);
    sprintf (xml, "<ulink url=\'%s\'>%s</ulink>", str, str);
    return xml;
}

char*
at_bullet ()
{
    return strdup ("&bull;");
}

char*
at_minus ()
{
    return strdup ("&minus;");
}

char*
createXmlFile (nam)
char * nam;
{
    if (first_pass)
    {
	addName (nam, 1);
	return NULL;
    }

    LIST * sn = searchName (nam);
    char * namXml, * funnam;
  
    if (sn->dup > 1)
    {
	funnam = malloc (strlen (nam) + 5 + 2 + 1);
	sprintf (funnam, "%s_dup_%i", nam, sn->dup);
	namXml = malloc (strlen (output_dir) + 1 + strlen (nam) + 5 + 2 + 4 + 1);
	sprintf (namXml, "%s/%s.xml", output_dir, funnam);
	--sn->dup;
    }
    else if (sn->dup == 1)
    {
	funnam = strdup (nam);
	namXml = malloc (strlen (output_dir) + 1 + strlen (nam) + 4 + 1);
	sprintf (namXml, "%s/%s.xml", output_dir, nam);
    }
  
    //fprintf (stdout, "Generating %s\n", str);
    fd = fopen (namXml, "w");
  
    if (!fd)
    {
	fprintf (stderr, "Error : cannot create file %s\n", namXml);
	fprintf (stderr, "%s\n", strerror(errno));
	freeListNames ();
	exit (0);
	return NULL;
    }

    free (namXml);
  
    return funnam;
}

char*
at_deffn ()
{
    char * nam, * nam1, * xml, * sxml, * fn, * funnam, * str, * str1;
    int arg = getNbArg ();
    int i;
  
    if (arg < 2)
	return NULL;
  
    nam = getArg (2);
    nam1 = searchPnames (nam);
    fn = modifyName (nam);
    funnam = createXmlFile (fn);
  
    currentFunNam = strdup (nam);
    if (nam1)
    {
	str = malloc (32 + strlen (getArg (1)) + 1 + strlen (nam) + 1);
	str1 = modifyNameForRefname (nam1);
	sprintf (str, "Scilab equivalent of the Maxima %s %s", getArg (1), nam);
    }
    else
    {
	str = malloc (7 + strlen (getArg (1)) + 1);
	str1 = modifyNameForRefname (nam);
	sprintf (str, "Maxima %s", getArg (1));
    }
  

    pushsw (1);
    pushsp (1);
  
    xml = malloc (2048);
    sxml = xml;
    xml += sprintf (xml, xmlbeg, funnam, str1, str);
    xml += sprintf (xml, "<title>Calling Sequence</title>\n<synopsis>");
    for (i = 2; i < arg; i++)
    {
	char *var = getArg (i);
	xml += sprintf (xml, "%s ", var);
    }
    xml += sprintf (xml, "%s</synopsis>\n</refsynopsisdiv>\n<refsection>\n<title>Description</title>\n", getArg (arg));
  
    free (funnam);
    free (fn);
    free (str);
    free (str1);  

    is_text = 0;
    deffnmode = 0;
  
    return sxml;
}

char*
at_end_deffn ()
{
    is_text = 0;
    insertText ("\n</refsection>\n</refentry>");
    if (!first_pass)
	fclose (fd);
    popsw ();
    popsp ();
    addFun2List ();
    args.nbargs = 0;
    return NULL;
}

char*
at_deffnx ()
{
    char * xml, * sxml;
    int arg = getNbArg ();
    if (arg < 2)
	return NULL;
    if (listmaxfun_dir)
    {
	if (args.nbargs != -1 && args.nbargs_deffnx != args.nbargs)
	    args.nbargs = -1;
	args.nbargs_deffnx = 0;
    }
  
    int i;
    xml = malloc (2048);
    sxml = xml;
    if (!first_pass)
	fseek (fd, -58, SEEK_CUR);
    xml += sprintf (xml, "<synopsis>");
    for (i = 2; i < arg; i++)
	xml += sprintf (xml, "%s", getArg (i));
    xml += sprintf (xml, "%s</synopsis>\n</refsynopsisdiv>\n<refsection>\n<title>Description</title>\n", getArg (arg));
  
    is_text = 0;
    deffnxmode = 0;    

    return sxml;
}

char*
at_defvr ()
{
    char * str, * xml, * sxml;
    int arg = getNbArg ();
    if (arg < 2)
	return NULL;
  
    int i;
    char * fn = modifyName (getArg (2));
    char * funnam = createXmlFile (fn);
    char * refname = modifyNameForRefname (getArg (2));

    pushsw (1);
    pushsp (1);
  
    xml = malloc (2048);
    sxml = xml;
    xml += sprintf (xml, xmlbeg, funnam, refname, getArg (1));
    xml += sprintf (xml, "<synopsis>");
    for (i = 2; i < arg; i++)
	xml += sprintf (xml, "%s ", getArg (i));
    xml += sprintf (xml, "%s</synopsis>\n</refsynopsisdiv>\n<refsection>\n<title>Description</title>\n", getArg (arg));
  
    free (funnam);
    free (fn);
    free (refname);
  
    is_text = 0;
    defvrmode = 0;

    return sxml;
}

char*
at_end_defvr ()
{
    is_text = 0;
    insertText ("\n</refsection>\n</refentry>");
    if (!first_pass)
	fclose (fd);
    popsw ();
    popsp ();
    return NULL;
}

char*
at_defvrx ()
{
    char * xml, * sxml;
    int arg = getNbArg ();
    if (arg < 2)
	return NULL;

    int i;
    xml = malloc (2048);
    sxml = xml;
    if (!first_pass)
	fseek (fd, -58, SEEK_CUR);
    xml += sprintf (xml, "<synopsis>");
    for (i = 2; i < arg; i++)
	xml += sprintf (xml, "%s", getArg (i));
    xml += sprintf (xml, "%s</synopsis>\n</refsynopsisdiv>\n<refsection>\n<title>Description</title>\n", getArg (arg));
  
    is_text = 0;

    return sxml;
}

char*
at_fnindex ()
{
    return NULL;
}

char*
at_vrindex ()
{
    return NULL;
}

char*
at_menu ()
{
    pushsw (0);
    return NULL;
}

char*
at_sp ()
{
    return NULL;
}

char*
at_end_menu ()
{
    popsw ();
    return NULL;
}

char*
at_table ()
{
    pushsw (writemode);
    pushit (nbitems);
    table_com = strdup (getArg (1));
    nbitems = 0;
    is_text = 0;
    pushsp (1);
    return strdup ("<variablelist>\n");
}

char*
at_end_table ()
{
    char * xml;

    if (nbitems)
	xml = strdup ("</listitem>\n</varlistentry>\n</variablelist>\n");
    else 
	xml = strdup ("</variablelist>\n");
    is_text = 0;
    popsp ();
    popsw ();
    nbitems = stackit[topit];
    popit ();
    return xml;
}

char*
at_itemize ()
{
    int nbarg = getNbArg ();
    char * arg;
    table_com = NULL;
    itemize_com = 1;
    pushsw (writemode);
    pushit (nbitems);
    nbitems = 0;
    is_text = 0;
    pushsp (1);
    if (nbarg == 1)
    {
	arg = getArg (1);
	if (!strcmp (arg, "&bull;"))
	    return strdup ("<itemizedlist mark=\'bullet\'>\n");
	if (!strcmp (arg, "&minus;"))
	    return strdup ("<itemizedlist mark=\'minus\'>\n");
    }
    return strdup ("<itemizedlist>\n");
}

char*
at_end_itemize ()
{
    char * xml;
    if (nbitems)
	xml = strdup ("</listitem>\n</itemizedlist>\n");
    else 
	xml = strdup ("</itemizedlist>\n");
    popsw ();
    nbitems = stackit[topit];
    popit ();
    popsp ();
    is_text = 0;
    return xml;
}

char*
at_enumerate ()
{
    itemize_com = 1;
    table_com = NULL;
    pushsw (writemode);
    pushit (nbitems);
    nbitems = 0;
    is_text = 0;
    pushsp (1);
    return strdup ("<orderedlist numeration=\'arabic\'>\n");
}

char*
at_end_enumerate ()
{
    char * xml;
    if (nbitems)
	xml = strdup ("</listitem>\n</orderedlist>\n");
    else 
	xml = strdup ("</orderedlist>\n");
    popsw ();
    nbitems = stackit[topit];
    popit ();
    popsp ();
    is_text = 0;
    itemize_com = 0;
    return xml;
}

char*
at_item ()
{
    if (table_com)
	return at_item_in_table ();
    else if (itemize_com)
	return at_item_in_itemize ();
}

char*
at_item_in_table ()
{
    char * str, * xml;
    int arg = getNbArg ();
    if (arg != 1)
	return NULL;
    execCommand (table_com, &str);
    xml = malloc (strlen (str) + 49 + 19 + 1);
    if (!nbitems)
	sprintf (xml, "<varlistentry>\n<term>%s</term>\n<listitem>\n", str);
    else 
	sprintf (xml, "</listitem>\n</varlistentry>\n<varlistentry>\n<term>%s</term>\n<listitem>\n", str);
    ++nbitems;
    free (str);
    is_text = 0;
    return xml;
}

char*
at_item_in_itemize ()
{
    char * xml;
    if (!nbitems)
	xml = strdup ("<listitem>\n");
    else 
	xml = strdup ("</listitem>\n<listitem>\n");
    ++nbitems;
    is_text = 0;
    return xml;
}

char*
at_ifinfo ()
{
    pushsw (0);
    return NULL;
}

char*
at_end_ifinfo ()
{
    popsw ();
    return NULL;
}

char*
at_ifhtml ()
{
    pushsw (writemode);
    return NULL;
}

char*
at_end_ifhtml ()
{
    popsw ();
    return NULL;
}

char*
at_html ()
{
    pushsw (writemode);
    return NULL;
}

char*
at_end_html ()
{
    popsw ();
    return NULL;
}

char*
at_tex ()
{
    pushsw (0);
    return NULL;
}

char*
at_end_tex ()
{
    popsw ();
    return NULL;
}

char*
at_flushleft ()
{
    pushsw (0);
    return NULL;
}

char*
at_end_flushleft ()
{
    popsw ();
    return NULL;
}

char*
at_iftex ()
{
    pushsw (0);
    return NULL;
}

char*
at_end_iftex ()
{
    popsw ();
    return NULL;
}

char*
at_ifnottex ()
{
    pushsw (writemode);
    return NULL;
}

char*
at_end_ifnottex ()
{
    popsw ();
    return NULL;
}

char*
at_ifnotinfo ()
{
    pushsw (writemode);
    return NULL;
}

char*
at_end_ifnotinfo ()
{
    popsw ();
    return NULL;
}

char*
at_node ()
{
    return NULL;
}

char*
at_section ()
{
    return NULL;
}

char*
at_chapter ()
{
    return NULL;
}

char*
at_noindent ()
{
    return NULL;
}

char*
at_appendix ()
{
    return NULL;
}

char*
at_footnotestyle ()
{
    return NULL;
}

char*
at_printindex ()
{
    return NULL;
}

char*
at_subsection ()
{
    return NULL;
}

char*
at_subsubsection ()
{
    return NULL;
}

char*
at_example ()
{
    pushsw (writemode);
    pushsp (0);
    is_text = 0;
    return strdup ("<programlisting role=\'example\'>\n");
}

char*
at_end_example ()
{
    popsw ();
    popsp ();
    is_text = 0;
    examplemode = 0;
    return strdup ("</programlisting>\n");
}

char*
at_smallformat ()
{
    pushsw (writemode);
    pushsp (0);
    is_text = 0;
    return strdup ("<programlisting role=\'example\'>\n");
}

char*
at_end_smallformat ()
{
    popsw ();
    popsp ();
    is_text = 0;
    return strdup ("</programlisting>\n");
}

char*
at_verbatim ()
{
    pushsw (writemode);
    pushsp (0);
    is_text = 0;
    return strdup ("<programlisting role=\'example\'>\n");
}

char*
at_end_verbatim ()
{
    popsw ();
    popsp ();
    is_text = 0;
    return strdup ("</programlisting>\n");
}
  
char*
at_end ()
{
    char * str, * str1, * xml;
    int arg = getNbArg ();
    if (arg != 1)
	return NULL;
    str = getArg (1);
    str1 = malloc (strlen (str) + 5 + 1);
    sprintf (str1, "@end_%s", str);
    execCommand (str1, &xml);
    free (str1);
    return xml;
}  
