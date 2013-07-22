function c=spherical_bessel_j(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('spherical_bessel_j',a,b)

endfunction
