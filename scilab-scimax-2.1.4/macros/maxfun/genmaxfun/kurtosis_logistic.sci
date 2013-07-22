function c=kurtosis_logistic(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('kurtosis_logistic',a,b)

endfunction
