function b=%sym_return(a)

if argn(2)~=1 then error(42), end
b=maxevalf('return',a)

endfunction
