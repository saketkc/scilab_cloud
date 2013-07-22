function d=%sym_coeff(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('coeff',a,b,c)

endfunction
