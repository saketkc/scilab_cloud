function c=inverse_jacobi_cn(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('inverse_jacobi_cn',a,b)

endfunction
