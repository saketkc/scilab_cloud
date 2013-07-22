function c=jacobi_ns(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_ns',a,b)

endfunction
