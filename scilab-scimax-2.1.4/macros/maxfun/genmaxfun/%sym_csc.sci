function b=%sym_csc(a)

if argn(2)~=1 then error(42), end
b=maxevalf('csc',a)

endfunction
