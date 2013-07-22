function d=cdf_binomial(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_binomial',a,b,c)

endfunction
