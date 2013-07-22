function d=quantile_f(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_f',a,b,c)

endfunction
