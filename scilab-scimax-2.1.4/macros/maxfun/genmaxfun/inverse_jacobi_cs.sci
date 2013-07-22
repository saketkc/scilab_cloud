function c=inverse_jacobi_cs(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('inverse_jacobi_cs',a,b)

endfunction
