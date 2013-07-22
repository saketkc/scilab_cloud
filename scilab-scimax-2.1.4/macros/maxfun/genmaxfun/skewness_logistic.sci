function c=skewness_logistic(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('skewness_logistic',a,b)

endfunction
