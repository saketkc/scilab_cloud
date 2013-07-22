function c=bessel_j(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('bessel_j',a,b)

endfunction
