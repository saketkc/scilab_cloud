function d=cdf_pareto(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_pareto',a,b,c)

endfunction
