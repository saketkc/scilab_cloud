function b=%sym_abs(a)

if argn(2)~=1 then error(42), end
b=maxevalf('abs',a)

endfunction
