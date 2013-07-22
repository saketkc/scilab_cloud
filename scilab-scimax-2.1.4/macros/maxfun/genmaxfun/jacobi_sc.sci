function c=jacobi_sc(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_sc',a,b)

endfunction
