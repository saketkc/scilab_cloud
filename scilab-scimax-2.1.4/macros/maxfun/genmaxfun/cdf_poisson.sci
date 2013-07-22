function c=cdf_poisson(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('cdf_poisson',a,b)

endfunction
