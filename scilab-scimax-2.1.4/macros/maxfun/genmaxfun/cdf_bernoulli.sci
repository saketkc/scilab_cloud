function c=cdf_bernoulli(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('cdf_bernoulli',a,b)

endfunction
