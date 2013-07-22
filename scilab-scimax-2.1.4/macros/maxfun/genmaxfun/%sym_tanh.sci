function b=%sym_tanh(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__tanh',a)

endfunction
