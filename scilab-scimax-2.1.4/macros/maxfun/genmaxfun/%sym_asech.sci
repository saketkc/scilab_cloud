function b=%sym_asech(a)

if argn(2)~=1 then error(42), end
b=maxevalf('asech',a)

endfunction
