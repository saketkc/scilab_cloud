function b=%sym_inv(a)

if argn(2)~=1 then error(42), end
b=maxevalf('inv',a)

endfunction
