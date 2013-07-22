function b=var_poisson(a)

if argn(2)~=1 then error(42), end
b=maxevalf('var_poisson',a)

endfunction
