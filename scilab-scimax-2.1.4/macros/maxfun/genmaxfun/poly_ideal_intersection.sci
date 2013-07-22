function d=poly_ideal_intersection(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('poly_ideal_intersection',a,b,c)

endfunction
