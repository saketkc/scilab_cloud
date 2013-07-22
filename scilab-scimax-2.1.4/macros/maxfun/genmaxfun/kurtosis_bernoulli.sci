function b=kurtosis_bernoulli(a)

if argn(2)~=1 then error(42), end
b=maxevalf('kurtosis_bernoulli',a)

endfunction
