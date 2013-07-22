function d=quantile_normal(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_normal',a,b,c)

endfunction
