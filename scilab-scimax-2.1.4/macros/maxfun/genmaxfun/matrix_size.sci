function b=matrix_size(a)

if argn(2)~=1 then error(42), end
b=maxevalf('matrix_size',a)

endfunction
