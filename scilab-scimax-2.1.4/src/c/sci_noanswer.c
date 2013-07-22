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
#include <signal.h>
#include <sys/types.h>
#include "maxsci1.h"

int 
sci_noanswer (fname)
     char *fname;
{
  CheckRhs (0, 0);
  CheckLhs (1, 1);

  quest_mode = 0;
  
  kill (pid, SIGINT);

  do VIDEOS;
  while (iseo (buf) == 0);

  LhsVar (1) = 0;
  return 0;
}
