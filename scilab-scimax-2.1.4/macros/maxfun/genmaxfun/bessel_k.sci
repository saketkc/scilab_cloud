function c=bessel_k(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('bessel_k',a,b)

endfunction
