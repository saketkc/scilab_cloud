%{
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

extern void insertAccent (char *, char *);
extern void insertStr (char *);
extern void insertStr2 (char *);
extern void insertWhite (char *);
extern void insertLBrace (void);
extern void insertRBrace (void);
extern void enterCommandMode (char *);
extern void closeCommandMode (void);
extern void enterSeeMode (char *);
extern void closeSeeMode (void);
extern void insertLdots (void);

int nblines = 0;

%}

%union {
  char * string;
}

%token <string> WHITE
%token EMPTY
%token LB
%token RB
%token CR
%token UMLAUT
%token ACUTE
%token GRAVE
%token SPACE
%token TILDE
%token NEWLINE
%token LINEBREAK
%token AT
%token LBRACE
%token RBRACE
%token <string> WORD
%token <string> COMMAND
%token LOWER
%token GREATER
%token AMP
%token QUOTE
%token APOS
%token DOT
%token LDOTS
%token <string> SEE

%%

file : lines 

lines : one_line lines | one_line  

one_line : text eol {insertStr2 ("\n");} | commandW | commandWC | commandCR | eol {closePara ();}

elems : one_elem elems | one_elem

one_elem : word | special_chars | lb text_with_cr rb | accent_com | special_com | commandLB

commandW : command WHITE text eol {closeCommandMode ();free ($2);}

commandLB : command lb text_with_cr rb {closeCommandMode ();}

commandWC : command WHITE commandCR {closeCommandMode ();free ($2);}

commandCR : command eol {closeCommandMode ();}

command : COMMAND {enterCommandMode ($1);}

text : elems | elems white | elems white text | white text | see
  
text_with_cr : /* empty */ | eol text_with_cr | white | text | text eol text_with_cr

lb : LB {insertLBrace ();}

rb : RB {insertRBrace ();}

white : WHITE {insertWhite ($1);}

word : WORD {insertStr ($1);}

see : SEE {enterSeeMode ($1);} text {closeSeeMode ();}

lower : LOWER {insertStr2 ("&lt;");}

greater : GREATER {insertStr2 ("&gt;");}

amp : AMP {insertStr2 ("&amp;");}

quote : QUOTE {insertStr2 ("\"");}

apos : APOS {insertStr2 ("\'");}

dot : DOT {insertStr2 (".");closeSeeMode ();}

ldots : LDOTS {insertLdots ();}

special_chars : lower | greater | amp | quote | apos | dot | ldots 
 
eol : CR {++nblines;} | EMPTY {++nblines;}

accent_com : UMLAUT WORD {insertAccent ("\"", $2);} | UMLAUT LB WORD RB {insertAccent ("\"", $3);}
             | ACUTE WORD {insertAccent ("\'", $2);} | ACUTE LB WORD RB {insertAccent ("\'", $3);} 
	     | TILDE WORD {insertAccent ("~", $2);} | TILDE LB WORD RB {insertAccent ("~", $3);}
             | GRAVE WORD {insertAccent ("`", $2);} | GRAVE LB WORD RB {insertAccent ("`", $3);}


special_com : SPACE {insertStr2 (" ");}
              | NEWLINE {insertStr2 ("\n");}
              | LINEBREAK {closePara ();}  
	      | AT {insertStr2 ("@");}
	      | LBRACE {insertStr2 ("{");}
	      | RBRACE {insertStr2 ("}");}

%%

int
yyerror (char *s)
{
  printf ("\nError in parsing at line %i\n", nblines + 1);
  exit (0);
  return (0);
}
