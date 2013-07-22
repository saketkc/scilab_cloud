function b=%sym_det(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__det',a)

endfunction
