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

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "stack-c.h"
#include "maxsci1.h"
#include "maxsci.h"

#define REAL 1 
#define COMPLEX 1 
#define POLYNOMIAL 2 
//#define SPARSE 5 
#define INT 8 
#define INT8 1
#define UINT8 11
#define INT16 2
#define UINT16 12
#define INT32 4
#define UINT32 14
#define STRING 10 
#define MLIST 17

int printStringMat (int *,int);
int gestionVar (int);

const static char tabs2a[247] = {48,49,50,51,52,53,54,55,56,57,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,95,35,33,36,32,40,41,59,58,43,45,42,47,92,61,46,44,39,91,93,37,124,38,60,62,126,94,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,0,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,96,0,0,0,125,123,34,0,0,0,0,0,0,0,0,0,0,0,0,9,0,63,0,0,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65};

#define printRealMat(type, mat, m, n, str1, str2, str3, str4)	\
  mn = m * n;							\
  								\
  if (mn == 1)							\
    {								\
      fprintf (is, str1, ((type)mat)[0]);			\
      break;							\
    }								\
  								\
  fprintf (is, "(Matrix(");					\
  								\
  for (i = 0; i < m - 1; i++)					\
    {								\
      Putc ('[', is);						\
      for (j = 0; j < n - 1; j++)				\
	{							\
	  fprintf (is, str2, ((type)mat)[j * m + i]);		\
	}							\
      fprintf (is, str3, ((type)mat)[(n - 1) * m + i]);		\
    }								\
  Putc ('[', is);						\
  for (j = 0; j < n - 1; j++)					\
    {								\
      fprintf (is, str2, ((type)mat)[j * m + m - 1]);		\
    }								\
  fprintf (is, str4, ((type)mat)[mn - 1])			


#define printCompMat(mat, m, n)				                \
  mn = m * n;								\
  									\
  if (mn == 1)								\
    {									\
      fprintf (is, "(%g%+g*%%i)", mat[0], mat[1]);			\
      break;								\
    }									\
  									\
  fprintf (is, "(Matrix(");						\
  									\
  for (i = 0; i < m - 1; i++)						\
    {									\
      Putc ('[', is);							\
      for (j = 0; j < n - 1; j++)					\
	{								\
	  fprintf (is, "%g%+g*%%i,", mat[j * m + i], mat[mn + j * m + i]);\
	}								\
      fprintf (is, "%g%+g*%%i],", mat[(n - 1) * m + i], mat[mn + (n - 1) * m + i]);\
    }									\
  Putc ('[', is);							\
  for (j = 0; j < n - 1; j++)						\
    {									\
      fprintf (is, "%g%+g*%%i,", mat[j * m + m - 1], mat[mn + j * m + m - 1]); \
    }									\
  fprintf (is, "%g%+g*%%i]))", mat[mn - 1], mat[2 * mn - 1])		
	
#define makePolynomF(var,deg,mat)		\
  for (k = 0; k < deg; k++)			\
    fprintf (is, "%+g*%s^%i", (mat)[k], var, k)

#define makePolynomC(var,deg,matR,matI)		\
  for (k = 0; k < deg; k++)			\
    fprintf (is, "+(%g%+g*%%i)*%s^%i", (matR)[k], (matI)[k], var, k)

void
printPolyRealMat (mat, m, n)
     double *mat;
     int m, n;
{					
  int len = 4;								
  char var[5];
  int *dec = (int*)mat + 4;		               			
  int k, mn = m * n;					
  register int i, j;
  
  C2F(cvstr)(&len, mat, var, &len, 4);				
  for (i = 0; var[i] != ' ' && i < 4; i++);           			
  var[i] = '\0';	                  	       			
  mat += 2 + m * n / 2;					
  
  if (mn == 1)                                                          
    {	                                                  
      Putc ('(', is);							
      makePolynomF (var, dec[1] - dec[0], mat + dec[0]);		
      Putc (')', is);					      		
      return;								
    }									
  
  fprintf (is, "(Matrix(");						
  									
  for (i = 0; i < m - 1; i++)						
    {									
      Putc ('[', is);							
      for (j = 0; j < n - 1; j++)					
	{								
	  makePolynomF (var, dec[m * j + i + 1] - dec[m * j + i], mat + dec[m * j + i]); 
	  Putc (',', is);							
	}								
      makePolynomF (var, dec[m * (n - 1) + i + 1] - dec[m * (n - 1)  + i], mat + dec[m * (n - 1) + i]); 
      Putc (']', is); Putc (',', is);						
    }									
  Putc ('[', is);							
  for (j = 0; j < n - 1; j++)						
    {									
      makePolynomF (var, dec[m * j + m] - dec[m * j + m - 1], mat + dec[m * j + m - 1]); 
      Putc (',', is);
    }									
  makePolynomF (var, dec[mn] - dec[mn - 1], mat + dec[mn - 1]);    	
  Putc (']', is); Putc (')', is); Putc (')', is);
}					

void
printPolyCompMat (mat, m, n)
     double *mat;
     int m, n;
{					
  int len = 4;								
  char var[5];
  int *dec = (int*)mat + 4;		               			
  int k, mn = m * n;					
  register int i, j;
  
  C2F(cvstr)(&len, mat, var, &len, 4);				
  for (i = 0; var[i] != ' ' && i < 4; i++);           			
  var[i] = '\0';	                  	       			
  mat += 2 + m * n / 2;					
  
  if (mn == 1)                                                          
    {	                                                  
      Putc ('(', is);							
      makePolynomC (var, dec[1] - dec[0], mat + dec[0], mat + dec[1]);		
      Putc (')', is);					      		
      return;								
    }									
  
  fprintf (is, "(Matrix(");						
  									
  for (i = 0; i < m - 1; i++)						
    {									
      Putc ('[', is);							
      for (j = 0; j < n - 1; j++)					
	{								
	  makePolynomC (var, dec[m * j + i + 1] - dec[m * j + i], mat + dec[m * j + i], mat + dec[mn] + dec[m * j + i]); 
	  Putc (',', is);							
	}								
      makePolynomC (var, dec[m * (n - 1) + i + 1] - dec[m * (n - 1)  + i], mat + dec[m * (n - 1) + i], mat + dec[mn] + dec[m * (n - 1) + i]); 
      Putc (']', is); Putc (',', is);						
    }									
  Putc ('[', is);							
  for (j = 0; j < n - 1; j++)						
    {									
      makePolynomC (var, dec[m * j + m] - dec[m * j + m - 1], mat + dec[m * j + m - 1], mat + dec[mn] + dec[m * j + m - 1]); 
      Putc (',', is);
    }									
  makePolynomC (var, dec[mn] - dec[mn - 1], mat + dec[mn - 1], mat + dec[mn] + dec[mn - 1]);    	
  Putc (']', is); Putc (')', is); Putc (')', is);
}

int
gestionVar (add)
     int add;
{
  int *header = istk (iadr (add));
  void *data = stk (add) + 2;
  register int i, j;
  int mn, k;
  char *var;

  if (add == 0)
    return -1;

  if (header[0] < 0)
    {
      add = header[1];
      header = istk (iadr (add));
      data = stk (add) + 2;
    }

  switch (header[0])
    {
    case REAL: //COMPLEX, POLYNOMIAL, INT, INT8, UINT8, INT16, UINT16, INT32, UINT32 :
      if (header[3] == COMPLEX)
	{
	  printCompMat (((double*)data), header[1], header[2]);
	}
      else 
	{
	  printRealMat (double*, data, header[1], header[2], "(%g)", "%g,", "%g],", "%g]))");
	}
      break;
    case INT :
      switch (header[3])
	{
	case INT8 :
	  printRealMat (char*, data, header[1], header[2], "(%i)", "%i,", "%i],", "%i]))");
	  break;
      	case UINT8 :
	  printRealMat (unsigned char*, data, header[1], header[2], "(%u)", "%u,", "%u],", "%u]))");
	  break;
	case INT16 :
	  printRealMat (short int*, data, header[1], header[2], "(%hi)", "%hi,", "%hi],", "%hi]))");
	  break;
      	case UINT16 :
	  printRealMat (unsigned short int*, data, header[1], header[2], "(%hu)", "%hu,", "%hu],", "%hu]))");
	  break;
	case INT32 :
	  printRealMat (int*, data, header[1], header[2], "(%i)", "%i,", "%i],", "%i]))");
	  break;
      	case UINT32 :
	  printRealMat (unsigned int*, data, header[1], header[2], "(%u)", "%u,", "%u],", "%u]))");
	  break;
	}
      break;
    case POLYNOMIAL :
      if (header[3] == COMPLEX)
	{
	  printPolyCompMat (((double*)data), header[1], header[2]);
	}
      else 
	{
	  printPolyRealMat (((double*)data), header[1], header[2]);
	}
      break;
    case MLIST :
      // h1=3 elmts,h11-h10=3=strlen("sym"),h14,h15,h16='s','y','m'
      //0 ,1,2,3,4 ,5 ,  6 ,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,  22,23,24,25,26,27,28 ,29,  30,31,32,...
      //17,3,1,9,13,18,  10,3,1,0,1 ,4 ,5 ,8 ,28,34,22,29,27,14,25,29,  10,1 ,1 ,0 ,1 ,2 ,-22,24,  10, 1, 1,...
      //  ,n,            Str 3x1             ,s ,y ,m ,t ,r ,e ,p ,  ,  Str 1x1          ,M  ,  ,  Str 1x1 ...
      //6+2*(h4-1)=debut rep;6+2*(h5-1)=fin rep
      if (header[1] != 3 || header[11] != 4 || header[14] != 28 || header[15] != 34 || header[16] != 22)
	return -1;
      return printStringMat (header + 30, header[28]);
    case STRING :
      return printStringMat (header, -22);
    default : 
      return -1;
    }
  return 0;
}  
  
int
printStringMat (header,type)
     int *header, type;
{
  register int k;
  int mn = header[1] * header[2];
  char Open = '(', Close = ')';

  if (type == -54)
    {
      Open = '{';
      Close = '}';
    }
  else if (type == 54)
    {
     Open = '[';
     Close = ']';
    } 

  if (mn == 1)
    {
      Putc (Open, is);
      for (k = 6; k < header[5] + 5; k++)
	{
	  if (header[k] >= 227)
	    Putc (header[k] - 100, is);
	  else 
	    Putc (tabs2a[(unsigned char)(header[k])], is);
	}
      Putc (Close, is);
      return 0;
    }

  Putc ('(', is);

  if (type == -22) 
    {
      Putc ('M', is);Putc ('a', is);Putc ('t', is);Putc ('r', is);Putc ('i', is);Putc ('x', is);Putc ('(', is);
      Open = '[';
      Close = ']';
    }
  
  int p;
  register int i, j;

  for (i = 0; i < header[1]; i++)
    {
      Putc (Open, is);
      p = i + 4;
      for (j = 0; j < header[2]; j++)
	{
	  for (k = 4 + mn + header[p]; k < 4 + mn + header[p + 1]; k++)
	    {
	      if (header[k] >= 227)
		Putc (header[k] - 100, is);
	      else 
		Putc (tabs2a[(unsigned char)(header[k])], is);
	    }
	  if (j != header[2] - 1)
	    Putc (',', is);
	  else if (i != header[1] - 1)
	    {
	      Putc (Close, is);
	      Putc (',', is);
	    }
	  else 
	    {
	      Putc (Close, is);
	      Putc (')', is);
	      if (type == -22)
		Putc (')', is);
	    }
	  p += header[1];
	}
    }
  return 0;
}
