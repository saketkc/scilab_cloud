function b=f90(a)

if argn(2)~=1 then error(42), end
b=maxevalf('f90',a)

endfunction
