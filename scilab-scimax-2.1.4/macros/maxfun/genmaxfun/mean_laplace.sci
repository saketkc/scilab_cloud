function c=mean_laplace(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('mean_laplace',a,b)

endfunction
