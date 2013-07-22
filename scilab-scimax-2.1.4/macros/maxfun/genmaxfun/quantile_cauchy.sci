function d=quantile_cauchy(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_cauchy',a,b,c)

endfunction
