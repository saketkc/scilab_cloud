function c=var_lognormal(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('var_lognormal',a,b)

endfunction
