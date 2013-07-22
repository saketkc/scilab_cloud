function c=jacobi(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi',a,b)

endfunction
