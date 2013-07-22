function b=%sym_coshm(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__coshm',a)

endfunction
