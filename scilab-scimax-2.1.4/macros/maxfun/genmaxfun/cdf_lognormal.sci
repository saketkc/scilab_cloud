function d=cdf_lognormal(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_lognormal',a,b,c)

endfunction
