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

#include "texi_yy.tab.h"
%}


white             [\t ]+
cr                {white}*[\n]
word              [^@\t\n{}\<\>&\"\'\. ]+
command           [^@\`\"\'{}~\t\n\* ]+

%%
{word}                                {yylval.string = strdup (yytext);return WORD;}
{white}                               {yylval.string = strdup (yytext);return WHITE;}
\{                                    {return LB;}
\}                                    {return RB;}
{cr}                                  {return CR;}
@{command}                            {yylval.string = strdup (yytext);return COMMAND;}
{white}*@c{white}[^\n]*{cr}           {return EMPTY;}
{white}*@c{cr}                        {return EMPTY;}
{white}*@comment{white}[^\n]*{cr}     {return EMPTY;}
@\"                                   {return UMLAUT;}
@\'                                   {return ACUTE;}
@\`                                   {return GRAVE;}
@{white}                              {return SPACE;}
@~                                    {return TILDE;}
@\n                                   {return NEWLINE;}
@\*                                   {return LINEBREAK;}
@@                                    {return AT;}
@\{                                   {return LBRACE;}
@\}                                   {return RBRACE;}
\"                                    {return QUOTE;}
\'                                    {return APOS;}
\<                                    {return LOWER;}
\>                                    {return GREATER;}
&                                     {return AMP;}
\.                                    {return DOT;}
\.\.\.                                {return LDOTS;} 
See{white}                            {yylval.string = strdup (yytext);return SEE;}
Also{white}see{white}                 {yylval.string = strdup (yytext);return SEE;}
see{white}also{white}                 {yylval.string = strdup (yytext);return SEE;}
\(see{white}                          {yylval.string = strdup (yytext);return SEE;}   
<<EOF>>                               {return 0;}
%%
