function d=poly_lcm(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('poly_lcm',a,b,c)

endfunction
