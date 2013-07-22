function b=%sym_gamma(a)

if argn(2)~=1 then error(42), end
b=maxevalf('gamma',a)

endfunction
