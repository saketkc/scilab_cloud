function c=var_logistic(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('var_logistic',a,b)

endfunction
