function b=%sym_acosh(a)

if argn(2)~=1 then error(42), end
b=maxevalf('acosh',a)

endfunction
