function c=skewness_continuous_uniform(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('skewness_continuous_uniform',a,b)

endfunction
