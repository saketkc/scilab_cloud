function b=adjoint(a)

if argn(2)~=1 then error(42), end
b=maxevalf('adjoint',a)

endfunction
