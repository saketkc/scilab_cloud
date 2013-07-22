function b=%sym_sin(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__sin',a)

endfunction
