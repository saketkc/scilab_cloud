function b=%sym_sech(a)

if argn(2)~=1 then error(42), end
b=maxevalf('sech',a)

endfunction
