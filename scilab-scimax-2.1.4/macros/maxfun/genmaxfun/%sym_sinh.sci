function b=%sym_sinh(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__sinh',a)

endfunction
