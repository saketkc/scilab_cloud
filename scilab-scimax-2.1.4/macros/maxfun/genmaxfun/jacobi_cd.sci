function c=jacobi_cd(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('jacobi_cd',a,b)

endfunction
