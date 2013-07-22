function d=cdf_negative_binomial(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_negative_binomial',a,b,c)

endfunction
