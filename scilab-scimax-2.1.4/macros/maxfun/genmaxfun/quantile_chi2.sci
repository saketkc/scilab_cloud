function c=quantile_chi2(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('quantile_chi2',a,b)

endfunction
