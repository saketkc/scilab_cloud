mode(-1);
output=unix_g('maxima -q --batch-string "":lisp (load \""make.lisp\"")""');

global %lisp_error;

%lisp_error=%F;

if (output($) == 'ERROR') then
  %lisp_error=%T;
end

for i=output',
  if (i <> '') then printf("%s\n",i), end;
end;

clear output