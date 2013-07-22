function d=quantile_lognormal(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_lognormal',a,b,c)

endfunction
