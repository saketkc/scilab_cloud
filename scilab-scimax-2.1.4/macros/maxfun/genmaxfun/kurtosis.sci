function b=kurtosis(a)

if argn(2)~=1 then error(42), end
b=maxevalf('kurtosis',a)

endfunction
