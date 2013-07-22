function c=jacobi_nc(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_nc',a,b)

endfunction
