function b=%sym_system(a)

if argn(2)~=1 then error(42), end
b=maxevalf('system',a)

endfunction
