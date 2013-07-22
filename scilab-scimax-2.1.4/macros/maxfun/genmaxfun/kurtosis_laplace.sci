function c=kurtosis_laplace(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('kurtosis_laplace',a,b)

endfunction
