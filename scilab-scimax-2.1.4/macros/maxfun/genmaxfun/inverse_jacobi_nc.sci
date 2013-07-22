function c=inverse_jacobi_nc(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('inverse_jacobi_nc',a,b)

endfunction
