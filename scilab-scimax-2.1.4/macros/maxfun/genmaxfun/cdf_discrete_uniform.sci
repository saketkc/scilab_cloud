function c=cdf_discrete_uniform(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('cdf_discrete_uniform',a,b)

endfunction
