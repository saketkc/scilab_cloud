function d=assoc_legendre_q(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('assoc_legendre_q',a,b,c)

endfunction
