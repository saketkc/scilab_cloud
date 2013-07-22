function c=jacobi_dn(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_dn',a,b)

endfunction
