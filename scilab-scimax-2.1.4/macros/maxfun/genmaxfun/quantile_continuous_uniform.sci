function d=quantile_continuous_uniform(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_continuous_uniform',a,b,c)

endfunction
