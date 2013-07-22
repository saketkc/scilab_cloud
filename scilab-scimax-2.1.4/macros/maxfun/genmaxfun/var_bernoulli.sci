function b=var_bernoulli(a)

if argn(2)~=1 then error(42), end
b=maxevalf('var_bernoulli',a)

endfunction
