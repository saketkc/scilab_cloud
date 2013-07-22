function c=jacobi_sn(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_sn',a,b)

endfunction
