function d=poly_expt(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('poly_expt',a,b,c)

endfunction
