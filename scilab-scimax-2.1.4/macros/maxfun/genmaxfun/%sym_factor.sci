function b=%sym_factor(a)

if argn(2)~=1 then error(42), end
b=maxevalf('factor',a)

endfunction
