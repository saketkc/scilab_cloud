function c=kurtosis_pareto(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('kurtosis_pareto',a,b)

endfunction
