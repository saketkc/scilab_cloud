function b=std_poisson(a)

if argn(2)~=1 then error(42), end
b=maxevalf('std_poisson',a)

endfunction
