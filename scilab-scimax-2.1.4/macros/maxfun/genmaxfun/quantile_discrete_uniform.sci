function c=quantile_discrete_uniform(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('quantile_discrete_uniform',a,b)

endfunction
