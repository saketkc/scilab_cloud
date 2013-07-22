function c=skewness_binomial(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('skewness_binomial',a,b)

endfunction
