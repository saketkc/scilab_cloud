function d=cdf_laplace(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_laplace',a,b,c)

endfunction
