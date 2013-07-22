function d=cdf_beta(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_beta',a,b,c)

endfunction
