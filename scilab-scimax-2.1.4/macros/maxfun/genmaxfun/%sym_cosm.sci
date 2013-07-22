function b=%sym_cosm(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__cosm',a)

endfunction
