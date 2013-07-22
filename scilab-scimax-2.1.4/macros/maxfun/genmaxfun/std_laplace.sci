function c=std_laplace(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('std_laplace',a,b)

endfunction
