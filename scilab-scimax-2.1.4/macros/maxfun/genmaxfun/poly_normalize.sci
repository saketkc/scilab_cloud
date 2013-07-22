function c=poly_normalize(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('poly_normalize',a,b)

endfunction
