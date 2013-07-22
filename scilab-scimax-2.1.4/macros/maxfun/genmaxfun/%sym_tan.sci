function b=%sym_tan(a)

if argn(2)~=1 then error(42), end
b=maxevalf('tan',a)

endfunction
