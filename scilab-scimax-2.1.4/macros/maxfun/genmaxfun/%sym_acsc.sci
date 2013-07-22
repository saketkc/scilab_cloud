function b=%sym_acsc(a)

if argn(2)~=1 then error(42), end
b=maxevalf('acsc',a)

endfunction
