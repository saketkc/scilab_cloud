function c=kronecker_product(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('kronecker_product',a,b)

endfunction
