function d=poly_normal_form(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('poly_normal_form',a,b,c)

endfunction
