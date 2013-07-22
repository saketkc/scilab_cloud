function b=%sym_cosh(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__cosh',a)

endfunction
