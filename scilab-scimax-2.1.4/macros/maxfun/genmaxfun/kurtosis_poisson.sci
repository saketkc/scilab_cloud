function b=kurtosis_poisson(a)

if argn(2)~=1 then error(42), end
b=maxevalf('kurtosis_poisson',a)

endfunction
