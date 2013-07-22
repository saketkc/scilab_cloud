function d=quantile_gumbel(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_gumbel',a,b,c)

endfunction
