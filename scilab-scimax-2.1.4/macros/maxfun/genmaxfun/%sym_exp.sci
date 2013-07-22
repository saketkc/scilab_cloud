function b=%sym_exp(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__exp',a)

endfunction
