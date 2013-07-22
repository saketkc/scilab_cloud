function b=%sym_ascii(a)

if argn(2)~=1 then error(42), end
b=maxevalf('ascii',a)

endfunction
