function c=poly_expand(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('poly_expand',a,b)

endfunction
