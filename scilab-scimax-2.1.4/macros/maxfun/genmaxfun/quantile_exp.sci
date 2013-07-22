function c=quantile_exp(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('quantile_exp',a,b)

endfunction
