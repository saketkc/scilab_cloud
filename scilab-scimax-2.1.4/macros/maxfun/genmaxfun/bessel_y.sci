function c=bessel_y(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('bessel_y',a,b)

endfunction
