function c=quantile_rayleigh(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('quantile_rayleigh',a,b)

endfunction
