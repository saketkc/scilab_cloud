function b=%sym_close(a)

if argn(2)~=1 then error(42), end
b=maxevalf('close',a)

endfunction
