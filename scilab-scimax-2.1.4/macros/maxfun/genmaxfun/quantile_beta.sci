function d=quantile_beta(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_beta',a,b,c)

endfunction
