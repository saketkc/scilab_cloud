function c=jacobi_ds(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_ds',a,b)

endfunction
