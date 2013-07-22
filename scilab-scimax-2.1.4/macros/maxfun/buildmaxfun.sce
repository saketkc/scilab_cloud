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

mode(-1)

global pathgen
pathgen='genmaxfun/'
mkdir(pathgen)

global ov_fun
ov_fun=[]

global pNames
exec('./personnalizedNames.sce',-1)

maxmacros=lib('../')
mdelete(pathgen+'overload.sce')

exec('createmaxfun.sci',-1)
exec('listmaxfun.sce',-1)
exec('personnalizedMaxfun.sce',-1)

printf("Compiling maxfunlib...\n\n")
path=get_absolute_file_path('buildmaxfun.sce')+pathgen
tbx_build_macros(TOOLBOX_NAME+'_maxfun', path);

printf("\nTake care, the functions below should be overloaded : \n")

ch=''
for i=ov_fun, ch=ch+i+',', end
disp(ch)

printf("\n\nThe file %soverload.sce has been generated.\n",path)

printf("Please check it and compare with %spersonnalizedOverload.sce.\n\n",get_absolute_file_path('buildmaxfun.sce'))

clear ch pathgen path ov_fun pNames maxmacros i;
