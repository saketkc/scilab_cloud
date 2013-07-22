function b=mean_poisson(a)

if argn(2)~=1 then error(42), end
b=maxevalf('mean_poisson',a)

endfunction
