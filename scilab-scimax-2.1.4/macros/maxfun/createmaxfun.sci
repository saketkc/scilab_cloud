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

function createmaxfun (maxnam,narg)

global pathgen
global ov_fun
global pNames

scinam=maxnam

s=size(pNames)
s=s(1)
for i=1:s
  if pNames(i,1)==maxnam then
    scinam=pNames(i,2)
    break
  end
end

//on teste la presence d'une fonction maxnam dans Scilab
try
  //je n'utilise pas eval car il y a un bug que je supprime en ne
  //compilant pas %eval => 'n'
  deff('a=%eval()','a=type('+scinam+')','n')
  t=%eval()
catch
  t=0
end  

if t==130 then
  scinam='%sym_'+scinam
else
  if (t==11)|(t==13) then
    types=['s' 'c' 'p' 'r']
    ch = 'overload('''+scinam+''','+sci2exp(types)+')'
    fd=mopen(pathgen+'overload.sce','a')
    mputl(ch,fd)
    mclose(fd)
    ov_fun=[ov_fun scinam]
    scinam='%sym_'+scinam
  end
end  

//puis on cree la function scinam.sci interfacant la fonction
//Maxima maxnam
chvar=''
chclo=''','
ill=''
chret='a'
test=''
if narg==-1 then chvar='varargin)',ill='l', else
  if narg~=0 then
    for i=1:narg-1	
      chvar = chvar+code2str(9+i)+','
    end
    chvar = chvar+code2str(9+narg)+')'
    chret = code2str(10+narg)
  else
    chvar = ')'
    chclo = ''''
  end
  test = 'if argn(2)~='+string(narg)+' then error(42), end'
end
ch=['function '+chret+'='+scinam+'('+chvar,'',test,chret+'=maxevalf'+ill+'('''+maxnam+chclo+chvar,'','endfunction']
mputl(ch,pathgen+scinam+'.sci')

endfunction
