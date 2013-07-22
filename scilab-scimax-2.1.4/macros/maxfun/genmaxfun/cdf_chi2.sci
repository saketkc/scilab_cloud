function c=cdf_chi2(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('cdf_chi2',a,b)

endfunction
