function b=%sym_denom(a)

if argn(2)~=1 then error(42), end
b=maxevalf('denom',a)

endfunction
