function d=quantile_gamma(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_gamma',a,b,c)

endfunction
