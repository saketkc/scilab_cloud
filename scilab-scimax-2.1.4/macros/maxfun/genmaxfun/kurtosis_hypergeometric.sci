function d=kurtosis_hypergeometric(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('kurtosis_hypergeometric',a,b,c)

endfunction
