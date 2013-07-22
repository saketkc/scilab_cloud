function c=jacobi_dc(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_dc',a,b)

endfunction
