function b=%sym_csch(a)

if argn(2)~=1 then error(42), end
b=maxevalf('csch',a)

endfunction
