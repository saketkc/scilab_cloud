function b=%sym_asinh(a)

if argn(2)~=1 then error(42), end
b=maxevalf('asinh',a)

endfunction
