function c=bessel_i(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('bessel_i',a,b)

endfunction
