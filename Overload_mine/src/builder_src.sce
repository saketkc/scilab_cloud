ici=get_absolute_file_path('builder_src.sce');
cd(ici);
exec('ilib_gen_gateway.sci', -1);

//we determine the number of functions we can load in a dynamic library
if funptr('sin') < 1000 then
  maxfuninlib=100;
  inc='';
else 
  maxfuninlib=1000;
  inc='#include <sci_gateway.h>';
end

fd=mopen('sci_dynlib.h','w');
mputl([inc;'#define MAXFUNINLIB '+string(maxfuninlib)],fd);
mclose(fd);

include='-I'+ici + ' -D__USE_DEPRECATED_STACK_FUNCTIONS__' ;
ldflags='-D __USE_DEPRECATED_STACK_FUNCTIONS__ -D __STD_C__';
files=['sci_overload.c','overstack.c','overfuns.f','sci_dynlib.h'];
//if MSDOS then
//  ldflags=SCI+'/bin/io_f.lib ' + SCI + '/bin/string.lib';
//  files=['sci_overload','overstack','overfuns','sci_dynlib','liboverload'];
//end

table = ['overload' 'sci_overload'];
for i=2:(maxfuninlib-1)
  table(i,:) = ['' '__rien__'];
end;

ilib_build('overload',table,files,[],'',ldflags,include,include,%f,'');

clear ici path include;
