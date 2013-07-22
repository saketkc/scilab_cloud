function d=cdf_logistic(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_logistic',a,b,c)

endfunction
