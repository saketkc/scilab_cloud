function b=%sym_apropos(a)

if argn(2)~=1 then error(42), end
b=maxevalf('apropos',a)

endfunction
