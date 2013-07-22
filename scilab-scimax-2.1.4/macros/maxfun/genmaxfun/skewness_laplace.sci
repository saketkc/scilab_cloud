function c=skewness_laplace(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('skewness_laplace',a,b)

endfunction
