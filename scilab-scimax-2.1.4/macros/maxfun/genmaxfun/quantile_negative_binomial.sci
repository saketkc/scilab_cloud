function d=quantile_negative_binomial(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_negative_binomial',a,b,c)

endfunction
