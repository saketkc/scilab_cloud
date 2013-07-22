function b=%sym_string(a)

if argn(2)~=1 then error(42), end
b=maxevalf('string',a)

endfunction
