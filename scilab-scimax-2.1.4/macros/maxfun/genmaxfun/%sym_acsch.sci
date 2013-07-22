function b=%sym_acsch(a)

if argn(2)~=1 then error(42), end
b=maxevalf('acsch',a)

endfunction
