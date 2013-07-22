function d=cdf_cauchy(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_cauchy',a,b,c)

endfunction
