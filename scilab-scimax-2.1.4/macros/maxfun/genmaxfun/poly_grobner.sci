function c=poly_grobner(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('poly_grobner',a,b)

endfunction
