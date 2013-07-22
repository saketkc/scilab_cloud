function c=jacobi_nd(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_nd',a,b)

endfunction
