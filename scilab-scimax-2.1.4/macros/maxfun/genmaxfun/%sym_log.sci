function b=%sym_log(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__log',a)

endfunction
