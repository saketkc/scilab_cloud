function b=kurtosis_exp(a)

if argn(2)~=1 then error(42), end
b=maxevalf('kurtosis_exp',a)

endfunction
