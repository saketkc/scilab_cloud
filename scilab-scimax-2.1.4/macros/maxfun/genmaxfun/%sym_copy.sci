function b=%sym_copy(a)

if argn(2)~=1 then error(42), end
b=maxevalf('copy',a)

endfunction
