function b=kurtosis_rayleigh(a)

if argn(2)~=1 then error(42), end
b=maxevalf('kurtosis_rayleigh',a)

endfunction
