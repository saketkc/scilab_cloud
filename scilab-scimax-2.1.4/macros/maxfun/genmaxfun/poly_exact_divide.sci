function d=poly_exact_divide(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('poly_exact_divide',a,b,c)

endfunction
