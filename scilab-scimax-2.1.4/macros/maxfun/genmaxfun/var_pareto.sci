function c=var_pareto(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('var_pareto',a,b)

endfunction
