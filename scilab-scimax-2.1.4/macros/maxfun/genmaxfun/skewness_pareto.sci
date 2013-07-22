function c=skewness_pareto(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('skewness_pareto',a,b)

endfunction
