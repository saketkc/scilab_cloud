function d=quantile_weibull(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_weibull',a,b,c)

endfunction
