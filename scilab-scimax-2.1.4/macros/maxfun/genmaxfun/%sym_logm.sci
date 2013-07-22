function b=%sym_logm(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__logm',a)

endfunction
