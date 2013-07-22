function c=poly_reduction(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('poly_reduction',a,b)

endfunction
