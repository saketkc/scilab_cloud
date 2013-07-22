function b=skewness_chi2(a)

if argn(2)~=1 then error(42), end
b=maxevalf('skewness_chi2',a)

endfunction
