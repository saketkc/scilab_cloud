function c=skewness_normal(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('skewness_normal',a,b)

endfunction
