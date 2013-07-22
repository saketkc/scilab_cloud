function c=jacobi_sd(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_sd',a,b)

endfunction
