function d=quantile_binomial(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_binomial',a,b,c)

endfunction
