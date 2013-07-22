function b=%sym_tanhm(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__tanhm',a)

endfunction
