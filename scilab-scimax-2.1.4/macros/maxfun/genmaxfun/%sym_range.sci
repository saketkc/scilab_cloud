function b=%sym_range(a)

if argn(2)~=1 then error(42), end
b=maxevalf('range',a)

endfunction
