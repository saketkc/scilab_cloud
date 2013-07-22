function b=var_discrete_uniform(a)

if argn(2)~=1 then error(42), end
b=maxevalf('var_discrete_uniform',a)

endfunction
