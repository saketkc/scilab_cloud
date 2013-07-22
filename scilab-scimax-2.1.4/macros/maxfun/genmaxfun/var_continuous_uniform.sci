function c=var_continuous_uniform(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('var_continuous_uniform',a,b)

endfunction
