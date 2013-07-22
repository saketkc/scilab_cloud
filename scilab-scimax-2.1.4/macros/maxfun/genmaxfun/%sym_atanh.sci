function b=%sym_atanh(a)

if argn(2)~=1 then error(42), end
b=maxevalf('atanh',a)

endfunction
