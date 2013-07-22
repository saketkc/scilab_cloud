function d=poly_elimination_ideal(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('poly_elimination_ideal',a,b,c)

endfunction
