function b=skewness_poisson(a)

if argn(2)~=1 then error(42), end
b=maxevalf('skewness_poisson',a)

endfunction
