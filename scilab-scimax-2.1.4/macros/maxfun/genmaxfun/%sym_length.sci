function b=%sym_length(a)

if argn(2)~=1 then error(42), end
b=maxevalf('length',a)

endfunction
