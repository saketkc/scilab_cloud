function b=%sym_sinm(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__sinm',a)

endfunction
