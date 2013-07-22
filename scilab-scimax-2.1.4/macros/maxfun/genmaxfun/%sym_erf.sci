function b=%sym_erf(a)

if argn(2)~=1 then error(42), end
b=maxevalf('erf',a)

endfunction
