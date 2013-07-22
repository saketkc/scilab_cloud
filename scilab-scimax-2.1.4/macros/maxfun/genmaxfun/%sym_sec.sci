function b=%sym_sec(a)

if argn(2)~=1 then error(42), end
b=maxevalf('sec',a)

endfunction
