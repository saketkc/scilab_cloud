function c=var_beta(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('var_beta',a,b)

endfunction
