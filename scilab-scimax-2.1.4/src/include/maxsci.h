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

#define SMFLOAT 1
#define SMFIXNUM8 2
#define SMFIXNUMU8 3
#define SMFIXNUM16 4
#define SMFIXNUMU16 5
#define SMFIXNUM32 6
#define SMFIXNUMU32 7
#define SMCOMPLEX 8
#define SMPOLYNOMF 9
#define SMPOLYNOMC 10
#define SMSTRING 11

#define MAXVARS 512

typedef struct {
  unsigned char type;
  long taille;
  int m;
  int n;
  int ptr;
} Info;

typedef struct {
  int vars;
  int appels; 
} Nb;

Info G_tabvar[MAXVARS];
Nb G_nb;
void * G_tabptr[MAXVARS];
