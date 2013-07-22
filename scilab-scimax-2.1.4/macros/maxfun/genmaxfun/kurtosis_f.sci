function c=kurtosis_f(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('kurtosis_f',a,b)

endfunction
