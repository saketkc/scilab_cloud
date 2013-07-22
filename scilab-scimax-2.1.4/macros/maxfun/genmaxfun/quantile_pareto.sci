function d=quantile_pareto(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('quantile_pareto',a,b,c)

endfunction
