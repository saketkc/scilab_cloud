function c=%sym_binomial(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('binomial',a,b)

endfunction
