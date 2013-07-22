function d=assoc_legendre_p(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('assoc_legendre_p',a,b,c)

endfunction
