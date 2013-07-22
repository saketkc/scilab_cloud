function b=%sym_sign(a)

if argn(2)~=1 then error(42), end
b=maxevalf('sign',a)

endfunction
