function c=kurtosis_gamma(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('kurtosis_gamma',a,b)

endfunction
