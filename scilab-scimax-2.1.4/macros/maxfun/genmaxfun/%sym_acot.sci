function b=%sym_acot(a)

if argn(2)~=1 then error(42), end
b=maxevalf('acot',a)

endfunction
