function c=var_laplace(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('var_laplace',a,b)

endfunction
