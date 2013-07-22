function c=jacobi_cn(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_cn',a,b)

endfunction
