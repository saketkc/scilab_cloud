function d=cdf_gamma(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_gamma',a,b,c)

endfunction
