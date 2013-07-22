function d=cdf_weibull(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_weibull',a,b,c)

endfunction
