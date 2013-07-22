function d=%sym_bezout(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('bezout',a,b,c)

endfunction
